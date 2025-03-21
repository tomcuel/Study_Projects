#include "obstacle_class.hpp"



//==========================================================================
// class Obstacle : polygonal obstacle
//==========================================================================

// member functions
//==========================================================================
// default constructor
Obstacle::Obstacle()
{

}
// obstacle with the list of sides and their properties
Obstacle::Obstacle(const vector<Arc*>& sides) : arcs(sides)
{

}
// apply padding to the obstacle
void Obstacle::apply_padding(double padding_distance, bool is_reversed)
{
    Point center = barycenter(*this);
    for (auto& arc : arcs) {
        for (auto& point : arc->points) {
            // expand each point away from the center of the obstacle
            Point direction = point - center;
            if (is_reversed) {
                direction.x = -direction.x;
                direction.y = -direction.y;
            }
            double magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
            if (magnitude > 0) {
                direction.x /= magnitude;
                direction.y /= magnitude;
                point.x += padding_distance * direction.x;
                point.y += padding_distance * direction.y;
            }
        }
    }
}
// export the obstacle to a file
void Obstacle::exporte(ostream& out) 
{
    for (Arc* arc : arcs) {
        arc->exporte(out);
    }
}

// external functions
//==========================================================================
// check if a point is stricly inside the obstacle
bool is_inside(const Point& P, const Obstacle& obstacle)
{
    int nb_intersections = 0;

    for (Arc* arc : obstacle.arcs){
        if (const Segment* seg = dynamic_cast<const Segment*>(arc)){
            // for a segment
            Point p1 = seg->points[0];
            Point p2 = seg->points[1];
            // Check if P is exactly on the segment (use cross product)
            double cross_product = (P.y - p1.y) * (p2.x - p1.x) - (P.x - p1.x) * (p2.y - p1.y);
            if (fabs(cross_product) < 1e-9) {  // P is collinear with the segment
                double dot_product1 = (P.x - p1.x) * (p2.x - p1.x) + (P.y - p1.y) * (p2.y - p1.y);
                double dot_product2 = (P.x - p2.x) * (p1.x - p2.x) + (P.y - p2.y) * (p1.y - p2.y);
                if (dot_product1 >= 0 && dot_product2 >= 0) {
                    return false;  // Point is exactly on the segment, not strictly inside
                }
            }
            // Check if the ray from P intersects the segment
            if ((p1.y > P.y) != (p2.y > P.y) && 
                P.x < (p2.x - p1.x) * (P.y - p1.y) / (p2.y - p1.y) + p1.x) {
                nb_intersections++;
            }
        }
        else if (const ArcCircle* arc_circle = dynamic_cast<const ArcCircle*>(arc)){
            // Check if P is inside the sector of the circle
            double dx = P.x - arc_circle->center.x;
            double dy = P.y - arc_circle->center.y;
            double distance_squared = dx * dx + dy * dy;
            double radius_squared = arc_circle->radius * arc_circle->radius;

            // P is within the circle (i.e., distance from center is less than the radius)
            if (distance_squared <= radius_squared){
                // Angle between point P and center
                double angle = atan2(dy, dx);
                if (angle < 0){
                    angle += 2 * M_PI; // Ensure angle is positive
                }
                // Check if the angle is within the arc's angular range
                if (arc_circle->angle1 <= angle && angle <= arc_circle->angle2){
                    nb_intersections++;  // Point P is within the arc's sector
                }
            }
        }
        else if (const ArcParameter* arc_param = dynamic_cast<const ArcParameter*>(arc)){
            // Approximate the point using the parametric function
            // You can sample the parameter space and check if the point matches
            double step = (arc_param->tf - arc_param->t0) / arc_param->nbt;
            for (double t = arc_param->t0; t <= arc_param->tf; t += step){
                Point sampled_point = arc_param->parametrisation(t);
                // Check if the sampled point is close to P (within a tolerance)
                if (fabs(sampled_point.x - P.x) < 1e-6 && fabs(sampled_point.y - P.y) < 1e-6){
                    nb_intersections++;  // Point P is on the parametric arc
                    break;
                }
            }
        }
        
    }

    // Point is inside if the number of intersections is odd
    return nb_intersections % 2 != 0;
}
// check if the given arc intersects with any arc in the obstacle
bool does_arc_intersect_obstacle(const Arc& arc, const Obstacle& obstacle)
{
    for (Arc* obstacle_arc : obstacle.arcs){
        if (const Segment* seg1 = dynamic_cast<const Segment*>(&arc)){
            if (const Segment* seg2 = dynamic_cast<const Segment*>(obstacle_arc)){
                // Check if two segments intersect
                if (do_segments_intersect(*seg1, *seg2)){
                    return true;
                }
            }
            else if (const ArcCircle* arc_circle = dynamic_cast<const ArcCircle*>(obstacle_arc)){
                // Check if the segment intersects with the arc circle
                if (do_segment_intersect_arc_circle(*seg1, *arc_circle)){
                    return true;
                }
            }
            else if (const ArcParameter* param_arc = dynamic_cast<const ArcParameter*>(obstacle_arc)){
                // Check if the segment intersects with the parametric arc
                if (do_segment_intersect_parametric(*seg1, *param_arc)){
                    return true;
                }
            }
        }
        else if (const ArcCircle* arc_circle = dynamic_cast<const ArcCircle*>(&arc)){
            if (const Segment* seg2 = dynamic_cast<const Segment*>(obstacle_arc)){
                // Check if the arc circle intersects with the segment
                if (do_segment_intersect_arc_circle(*seg2, *arc_circle)){
                    return true;
                }
            }
            else if (const ArcCircle* arc_circle2 = dynamic_cast<const ArcCircle*>(obstacle_arc)){
                // Check if two arc circles intersect
                if (do_arc_circle_intersect(*arc_circle, *arc_circle2)){
                    return true;
                }
            }
            else if (const ArcParameter* param_arc = dynamic_cast<const ArcParameter*>(obstacle_arc)){
                // Check if the arc circle intersects with the parametric arc
                if (do_arc_circle_intersect_parametric(*arc_circle, *param_arc)){
                    return true;
                }
            }
        }
        else if (const ArcParameter* param_arc = dynamic_cast<const ArcParameter*>(&arc)){
            if (const Segment* seg2 = dynamic_cast<const Segment*>(obstacle_arc)){
                // Check if the parametric arc intersects with the segment
                if (do_segment_intersect_parametric(*seg2, *param_arc)){
                    return true;
                }
            }
            else if (const ArcCircle* arc_circle = dynamic_cast<const ArcCircle*>(obstacle_arc)){
                // Check if the parametric arc intersects with the arc circle
                if (do_arc_circle_intersect_parametric(*arc_circle, *param_arc)){
                    return true;
                }
            }
            else if (const ArcParameter* param_arc2 = dynamic_cast<const ArcParameter*>(obstacle_arc)){
                // Check if two parametric arcs intersect
                if (do_parametric_intersect(*param_arc, *param_arc2)) {
                    return true;
                }
            }
        }
    }
    return false;
}
// check if the two obstacles intersect
bool do_obstacles_intersect(const Obstacle& obstacle1, const Obstacle& obstacle2)
{
    // there is an intersection if one point of the obstacle 1 is inside the obstacle 2 or vice versa
    for (Arc* arc : obstacle1.arcs){
        if (is_inside(arc->points[0], obstacle2) || is_inside(arc->points[1], obstacle2)){
            return true;
        }
    }
    for (Arc* arc : obstacle2.arcs){
        if (is_inside(arc->points[0], obstacle1) || is_inside(arc->points[1], obstacle1)){
            return true;
        }
    }
    // for the special case of a fully inside obstacle but that has all its points on the sides of the other obstacle
    // this is not treated since it's not a common case, and it's not our priority in this function
    // it will not happen in our track modelling for example
    return false;
}
// barycentre of the obstacle (only for polygonal obstacles for now)
Point barycenter(const Obstacle& obstacle)
{
    for (Arc* arc : obstacle.arcs){
        const Segment* seg = dynamic_cast<const Segment*>(arc);
        if (!seg){
            cout << "The obstacle is not a polygon" << endl;
            exit(-1);
        }
    }
    // getting all the obstacle points (vertices)
    vector<Point> vertices;
    for (Arc* arc : obstacle.arcs){
        const Segment* seg = dynamic_cast<const Segment*>(arc);
        vertices.push_back(seg->points[0]);
    }

    Point centroid(0,0);
    for (int i = 0; i < vertices.size(); i++){
        centroid.x += vertices[i].x;
        centroid.y += vertices[i].y;
    }
    centroid.x /= vertices.size();
    centroid.y /= vertices.size();
    return centroid;
}
// obstacle area  (only for polygonal obstacles for now)
double area(const Obstacle& obstacle)
{
    if (obstacle.arcs.size() < 3){
        cout << "The obstacle is not a polygon" << endl;
        exit(-1);
    }

    // getting all the obstacle points (vertices)
    vector<Point> vertices;
    for (Arc* arc : obstacle.arcs){
        const Segment* seg = dynamic_cast<const Segment*>(arc);
        vertices.push_back(seg->points[0]);
    }

    const Point& G = barycenter(obstacle); // handle if the obstacle is not a polygon
    double total_area = 0.0;
    for (int i=0; i<vertices.size(); i++){
        const Point& A = G;
        const Point& B = vertices[i];
        const Point& C = vertices[(i+1)%vertices.size()];
        total_area += surface(A, B, C);
    }
    return total_area;
}
// create an obstacle out of two obstacles that intersect (we know that they intersect before calling this function)
// limitations concerning complex obstacles, or even obstacles that have common sides but no strictly inside points, or even common sides only
Obstacle concatenate_obstacles(const Obstacle& obstacle1, const Obstacle& obstacle2)
{
    Obstacle concatenated_obstacle;

    for (Arc* arc_1 : obstacle1.arcs){
        const Segment* seg_1 = dynamic_cast<const Segment*>(arc_1);
        bool keep_seg_1 = true;

        // if the obstacle1 segment is fully inside the obstacle2, then we don't add it to the concatenated obstacle
        if (is_inside(seg_1->points[0], obstacle2) && is_inside(seg_1->points[1], obstacle2)){
            keep_seg_1 = false; 
            // we here don't take into account the case where the segment is on the side of the obstacle2
            // we also don't take care of the case where the segment extremities are within the obstacle2 but not the segment itself
        }

        for (Arc* arc_2 : obstacle2.arcs){
            const Segment* seg_2 = dynamic_cast<const Segment*>(arc_2);

            // if the obstacle2 segment is fully inside the obstacle1, then we don't add it to the concatenated obstacle
            if (is_inside(seg_2->points[0], obstacle1) && is_inside(seg_2->points[1], obstacle1)){
                continue; 
                // we here don't take into account the case where the segment is on the side of the obstacle1
                // we also don't take care of the case where the segment extremities are within the obstacle1 but not the segment itself
            }

            // if there is an intersection between the segment of the first obstacle and the segment of the second obstacle
            if (do_segments_intersect(*seg_1, *seg_2)){
            
                // it now depend on which points is inside the other obstacle
                Point obs_1_inside_point;
                Point obs_1_outside_point;
                if (is_inside(seg_1->points[0], obstacle2)){
                    obs_1_inside_point = seg_1->points[0];
                    obs_1_outside_point = seg_1->points[1];
                }
                else{
                    obs_1_inside_point = seg_1->points[1];
                    obs_1_outside_point = seg_1->points[0];
                }
                Point obs_2_inside_point;
                Point obs_2_outside_point;
                if (is_inside(seg_2->points[0], obstacle1)){
                    obs_2_inside_point = seg_2->points[0];
                    obs_2_outside_point = seg_2->points[1];
                }
                else{
                    obs_2_inside_point = seg_2->points[1];
                    obs_2_outside_point = seg_2->points[0];
                }

                // we now only add the segment that links the two outside points
                concatenated_obstacle.arcs.push_back(new Segment(obs_1_outside_point, obs_2_outside_point));
                keep_seg_1 = false;

            }
        }

        if (keep_seg_1){
            concatenated_obstacle.arcs.push_back(new Segment(seg_1->points[0], seg_1->points[1]));
        }
    }

    for (Arc* arc_2 : obstacle2.arcs){
        const Segment* seg_2 = dynamic_cast<const Segment*>(arc_2);
        bool keep_seg_2 = true;

        // if the obstacle2 segment is fully inside the obstacle1, then we don't add it to the concatenated obstacle
        if (is_inside(seg_2->points[0], obstacle1) && is_inside(seg_2->points[1], obstacle1)){
            keep_seg_2 = false; 
            // we here don't take into account the case where the segment is on the side of the obstacle1
            // we also don't take care of the case where the segment extremities are within the obstacle1 but not the segment itself
        }

        for (Arc* arc_1 : obstacle1.arcs){
            const Segment* seg_1 = dynamic_cast<const Segment*>(arc_1);

            // if the obstacle1 segment is fully inside the obstacle2, then we don't add it to the concatenated obstacle
            if (is_inside(seg_1->points[0], obstacle2) && is_inside(seg_1->points[1], obstacle2)){
                continue; 
                // we here don't take into account the case where the segment is on the side of the obstacle2
                // we also don't take care of the case where the segment extremities are within the obstacle2 but not the segment itself
            }

            // if there is an intersection between the segment of the first obstacle and the segment of the second obstacle
            if (do_segments_intersect(*seg_1, *seg_2)){
            
                // it now depend on which points is inside the other obstacle
                Point obs_1_inside_point;
                Point obs_1_outside_point;
                if (is_inside(seg_1->points[0], obstacle2)){
                    obs_1_inside_point = seg_1->points[0];
                    obs_1_outside_point = seg_1->points[1];
                }
                else{
                    obs_1_inside_point = seg_1->points[1];
                    obs_1_outside_point = seg_1->points[0];
                }
                Point obs_2_inside_point;
                Point obs_2_outside_point;
                if (is_inside(seg_2->points[0], obstacle1)){
                    obs_2_inside_point = seg_2->points[0];
                    obs_2_outside_point = seg_2->points[1];
                }
                else{
                    obs_2_inside_point = seg_2->points[1];
                    obs_2_outside_point = seg_2->points[0];
                }

                // we now only add the segment that links the two outside points
                concatenated_obstacle.arcs.push_back(new Segment(obs_1_outside_point, obs_2_outside_point));
                keep_seg_2 = false;

            }
        }

        if (keep_seg_2){
            concatenated_obstacle.arcs.push_back(new Segment(seg_2->points[0], seg_2->points[1]));
        }
    }


    // only keeping the unique segments in the concatenated obstacle
    Obstacle unique_concatenated_obstacle;
    for (Arc* all_arc : concatenated_obstacle.arcs){
        bool is_unique = true;
        for (Arc* unique_arc : unique_concatenated_obstacle.arcs){
            if ((all_arc->points[0] == unique_arc->points[0] && all_arc->points[1] == unique_arc->points[1]) || (all_arc->points[0] == unique_arc->points[1] && all_arc->points[1] == unique_arc->points[0])){
                is_unique = false;
                break;
            }
        }
        if (is_unique){
            unique_concatenated_obstacle.arcs.push_back(all_arc);
        }
    }
    return unique_concatenated_obstacle;
}
