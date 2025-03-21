#include "graph_class.hpp"



//==========================================================================
// class Graph : to setup the graph of the problem
//==========================================================================

// member functions
//==========================================================================
// constructor with only start and goal points
Graph::Graph(const Point& s, const Point& g) : start(s), goal(g)
{

}
// constructor with obstacles, start and goal points
Graph::Graph(const vector<Obstacle>& obs, const Point& s, const Point& g, bool are_obstacles_outer_and_inside_layout) : start(s), goal(g)
{
    for (auto ob : obs){
        (*this).add_obstacle(ob);
    }
}
// with the outer track, the inner track, and the linking obstacle
Graph::Graph(const Obstacle& outer_track, const Obstacle& inside_track, const Obstacle& linking_obstacle, vector<Arc*> middle_path, const Point& s, const Point& g) : start(s), goal(g)
{
    // Step 1: the outer track, the inner track, and the linking obstacle, border the path
    all_points = {start, goal};
    graph.clear();
    vector<Arc*> track_arcs;
    for (auto arc : outer_track.arcs) {
        track_arcs.push_back(arc);
        all_points.push_back(arc->points[0]);
    }
    for (auto arc : inside_track.arcs) {
        track_arcs.push_back(arc);
        all_points.push_back(arc->points[0]);
    }
    for (auto arc : linking_obstacle.arcs) {
        Segment* seg = static_cast<Segment*>(arc);
        // we need to check if the arc is not already in the graph to add it 
        bool already_in_graph = false;
        for (const auto& arc_graph : track_arcs){
            Segment* seg_graph = static_cast<Segment*>(arc_graph);
            if (are_segments_equal(*seg, *seg_graph)){
                already_in_graph = true;
                break;
            }
        }
        if (!already_in_graph){ // if the arc is not already in the graph, we add it
            track_arcs.push_back(arc);
        }
        else { // if the arc is already in the graph, we need to remove it from the graph
            vector<Arc*> new_graph;
            for (const auto& arc_graph : track_arcs){
                Segment* seg_graph = static_cast<Segment*>(arc_graph);
                if (!are_segments_equal(*seg, *seg_graph)){
                    new_graph.push_back(arc_graph);
                }
            }
            track_arcs = new_graph;
        }
    }
    // update the graph as one obstacle
    Obstacle point_container(track_arcs);
    obstacles = {point_container};

    // Step 2: add the middle path
    for (auto arc : middle_path){
        track_arcs.push_back(arc);
        if (arc->points[0] != start){
            all_points.push_back(arc->points[0]);
        }
    }
    // update the graph with all the current arcs
    graph = track_arcs;

    // Step 3: iterate over all pairs of points and link them if valid
    for (int i = 0; i < all_points.size(); ++i) {
        for (int j = i + 1; j < all_points.size(); ++j) {
            Segment candidate_segment(all_points[i], all_points[j]);
            
            // the segment must not already be in the graph
            bool already_in_graph = false;
            for (const auto& arc : graph){
                if ((arc->points[0] == all_points[i] && arc->points[1] == all_points[j]) || (arc->points[0] == all_points[j] && arc->points[1] == all_points[i])){
                    already_in_graph = true;
                    break;
                }
            }
            if (already_in_graph){
                continue; // skip this pair, already in the graph
            }

            // the created segment must not intersect any obstacle
            bool intersects_obstacle = false;
            for (const auto& obs : obstacles){
                if (does_arc_intersect_obstacle(candidate_segment, obs)){
                    intersects_obstacle = true;
                    break;
                }
            }
            if (intersects_obstacle){
                continue; // skip this pair, intersects an obstacle
            }

            // the created segment must intersect the middle path or have a least one point that is the start or the goal
            bool intersects_middle_path = false;
            for (const auto& arc : middle_path){
                const Segment* seg_path = dynamic_cast<const Segment*>(arc);
                if (do_segments_intersect(candidate_segment, *seg_path) || candidate_segment.points[0] == start || candidate_segment.points[1] == start || candidate_segment.points[0] == goal || candidate_segment.points[1] == goal){
                    intersects_middle_path = true;
                    break;
                }
            }
            if (!intersects_middle_path){
                continue; // skip this pair, doesn't intersect the middle path
            }

            // if all conditions are satisfied, add the segment as a new arc
            Arc* new_arc = new Segment(all_points[i], all_points[j]);
            graph.push_back(new_arc);
        }
    }
    
    // since we're considering the real track there with a lot of points, there will be not need to add the intersection points and cut the arcs that are overlapping
    // it could give us a better path, but then it would take ages to create the graph

}
// with obstacles, goal point, and a moving piece (that is the start point)
Graph::Graph(const vector<Obstacle>& obs, const Point& g, const Obstacle& mv_p, bool are_obstacles_outer_and_inside_layout) : goal(g), moving_piece(mv_p)
{   
    start = barycenter(mv_p);

    // calculate the padding distance for the moving piece
    double padding_distance = 0;
    for (const auto& arc : mv_p.arcs){
        for (const Point& point : arc->points){
            double distance = sqrt((start.x - point.x) * (start.x - point.x) + (start.y - point.y) * (start.y - point.y));
            if (distance > padding_distance){
                padding_distance = distance;
            }
        }
    }
    // two obstacles means that we have the inside and the outside of the track borders
    // the first obstacle is the inside of the track and the second is the outside of the track
    if (are_obstacles_outer_and_inside_layout){
        obstacles[0].apply_padding(padding_distance);
        obstacles[1].apply_padding(padding_distance, true);
    }
    // otherwise we apply the classic padding
    else {
        for (auto& obs : obstacles){
            obs.apply_padding(padding_distance);
        }
    }

    for (auto ob : obs){
        (*this).add_obstacle(ob);
    }
}
// add an obstacle to the graph and modify it if necessary
void Graph::add_obstacle(const Obstacle& ob)
{
    // adding the obstacle to the list of obstacles
    obstacles.push_back(ob);

    // reset the graph arcs and put all the arcs of the obstacles in the graph
    // also add all the points of the obstacles to the list of points
    all_points.clear();
    all_points.push_back(start);
    all_points.push_back(goal);
    graph.clear();
    for (auto obs : obstacles){
        for (auto arc : obs.arcs){
            graph.push_back(arc);
            all_points.push_back(arc->points[0]);
        }
    }

    // we now need to link all the sommets / points to every possible point 
    // - the segment between two points must not cross any obstacle to be added to the graph
    // - the arc we try to add must not intersect any other arc of the graph
    // - they also should not be already in the graph
    // - if the two considered points are part of an obstacle, then they have already been linked by an arc
    // Iterate over all pairs of points and link them if valid
    for (int i = 0; i < all_points.size(); ++i) {
        for (int j = i + 1; j < all_points.size(); ++j) {
            Segment candidate_segment(all_points[i], all_points[j]);

            // Rule 1: check if the two points belong to the same obstacle
            bool both_in_same_obstacle = false;
            for (const auto& obs : obstacles){
                bool p1_in_obstacle = false, p2_in_obstacle = false;
                for (const auto& arc : obs.arcs){
                    if (arc->points[0] == all_points[i] || arc->points[1] == all_points[i]){
                        p1_in_obstacle = true;
                    }
                    if (arc->points[0] == all_points[j] || arc->points[1] == all_points[j]){
                        p2_in_obstacle = true;
                    }
                    if (p1_in_obstacle && p2_in_obstacle){
                        both_in_same_obstacle = true;
                        break;
                    }
                }
                if (both_in_same_obstacle){
                    break;
                }
            }
            if (both_in_same_obstacle){
                continue; // skip this pair, already linked in the obstacle
            }

            // Rule 2: check if the segment already exists in the graph
            bool already_in_graph = false;
            for (const auto& arc : graph){
                if ((arc->points[0] == all_points[i] && arc->points[1] == all_points[j]) || (arc->points[0] == all_points[j] && arc->points[1] == all_points[i])){
                    already_in_graph = true;
                    break;
                }
            }
            if (already_in_graph){
                continue; // skip this pair, already in the graph
            }

            // Rule 3: check if the segment intersects any obstacle
            bool intersects_obstacle = false;
            for (const auto& obs : obstacles){
                if (does_arc_intersect_obstacle(candidate_segment, obs)){
                    intersects_obstacle = true;
                    break;
                }
            }
            if (intersects_obstacle){
                continue; // Skip this pair, intersects an obstacle
            }

            // if all conditions are satisfied, add the segment as a new arc
            Arc* new_arc = new Segment(all_points[i], all_points[j]);
            graph.push_back(new_arc);
        }
    }

    // any arc that is part of two obstacles must be removed from the graph
    vector<Arc*> new_obstacles_graph;
    for (int i = 0; i < graph.size(); ++i){
        const Segment* seg_i = dynamic_cast<const Segment*>(graph[i]);
        int nb_obstacles_for_arc = 0;
        for (int j = 0; j < obstacles.size(); ++j){
            for (Arc* arc : obstacles[j].arcs){
                const Segment* seg_j = dynamic_cast<const Segment*>(arc);
                if (is_segment_contained_within(*seg_i, *seg_j) || is_segment_contained_within(*seg_j, *seg_i)){
                    nb_obstacles_for_arc++;
                }
            }
        }
        if (nb_obstacles_for_arc <= 1){
            new_obstacles_graph.push_back(graph[i]);
        }
    }
    graph = new_obstacles_graph;

    // now for each arc, we look if it does intersect with any other arc of the graph
    // each time it does, we need to make 4 arcs and 1 node out of the intersection until we have no more intersections of arcs
     
    // finding all the intersection points
    int current_graph_size = graph.size();
    int i = 0;
    int j = 0;
    while (i != current_graph_size){
        const Segment* seg1 = dynamic_cast<const Segment*>(graph[i]);
        j = i+1;
        while (j != current_graph_size){
            const Segment* seg2 = dynamic_cast<const Segment*>(graph[j]);

            // looking if the two segments intersect we will have differents situations
            // intersection at a point that is not an extremity of the segments --> function do_segments_intersect
            // --> creation of 4 new arcs and 1 new point that is the intersection point
            // the two segments are overlapping
            // --> creation of 2 new arcs and 1 new point that is one of the extremities of a segment in the overlapping part
            // no intersection and overlapping but a common point, need to make some changes 
            // --> already linked by an arc so nothing to do

             // if the two segments intersect but not at an extremity
            if (do_segments_intersect(*seg1, *seg2) && !is_point_on_segment(seg1->points[0], *seg2) && !is_point_on_segment(seg1->points[1], *seg2) && !is_point_on_segment(seg2->points[0], *seg1) && !is_point_on_segment(seg2->points[1], *seg1)){
                // get the intersection point since there is an intersection
                Point intersection = get_segment_intersection(*seg1, *seg2);
                // add the intersection point to the list of points
                all_points.push_back(intersection);
            }
            j++;
        }
        i++;
    }

    // adding the newly created arcs
    for (int i=0; i<all_points.size(); ++i){
        for (int j=0; j<graph.size(); ++j){
            const Segment* seg = dynamic_cast<const Segment*>(graph[j]);
            // if the point is on the arc, the arc must be split into two arcs at this point since it's an intersection point
            if (is_point_on_segment(all_points[i], *seg) && all_points[i] != seg->points[0] && all_points[i] != seg->points[1]){
                Arc* new_arc1 = new Segment(seg->points[0], all_points[i]);
                Arc* new_arc2 = new Segment(all_points[i], seg->points[1]);
                graph.push_back(new_arc1);
                graph.push_back(new_arc2);
            }
        }
    }

    // suppress the arcs that overlapping arcs, those that are for example 
    // (1,1) -> (2,2) and (1,1) -> (1.5,1.5) and (1.5,1.5) -> (2,2)
    // become : (1,1) -> (1.5,1.5) and (1.5,1.5) -> (2,2) since (1,1) -> (2,2) is not needed anymore
    // adding the newly created arcs
    vector<bool> to_delete(graph.size(), false);
    for (int i=0; i<graph.size(); ++i){
        const Segment* seg_i = dynamic_cast<const Segment*>(graph[i]);
        for (int j=0; j<graph.size(); ++j){
            if (i == j){
                continue;
            }
            const Segment* seg_j = dynamic_cast<const Segment*>(graph[j]);
            if (are_segments_collinear(*seg_i, *seg_j)){
                if (is_segment_contained_within(*seg_i, *seg_j)){
                    to_delete[i] = true;
                }
                if (is_segment_contained_within(*seg_j, *seg_i)){
                    to_delete[j] = true;
                }
            }
        }
    }
    vector<Arc*> new_graph;
    for (int i=0; i<graph.size(); ++i){
        if (!to_delete[i]){
            new_graph.push_back(graph[i]);
        }
    }
    graph = new_graph;
}
// apply padding to the obstacles in case of a moving piece (2D not only a point)
void Graph::apply_padding_to_obstacles()
{
    // if the moving piece is an object (2D), we need to apply padding to the obstacles
    // we modify every obstacle in the list of obstacles to make as if we were dealing with a point
    // this point is the barycenter of the moving piece and we add a padding to the obstacles that is the distance between the barycenter and the closest point of the obstacle
    // we first suppose that the moving piece is a rectangle to simplify the problem 
    vector<Obstacle> old_obstacles = obstacles;
    for (auto& obs : old_obstacles){
        double min_distance = numeric_limits<double>::max();

        // calculate the closest distance between the barycenter and the obstacle
        for (const auto& arc : obs.arcs){
            for (const Point& point : arc->points){
                Point bary = barycenter(moving_piece);
                double distance = sqrt((bary.x - point.x) * (bary.x - point.x) + (bary.y - point.y) * (bary.y - point.y)); // Euclidean distance
                if (distance < min_distance){
                    min_distance = distance;
                }
            }
        }
        // expand the obstacle by the padding (min_distance)
        obs.apply_padding(min_distance);
    }

    // we need to update the graph with the new obstacles, so we clear it and add the new obstacles
    obstacles.clear();
    for (auto& obs : old_obstacles){
        (*this).add_obstacle(obs);
    }
}
// build the adjacency matrix for the graph
vector<vector<double>> Graph::build_adjacency_matrix() 
{
    int n = all_points.size();
    // put all values to infinity
    vector<vector<double>> adj_matrix(n, vector<double>(n, INF));

    // initialize diagonal to zero (cost from a point to itself is 0)
    for (int i = 0; i < n; ++i){
        adj_matrix[i][i] = 0;
    }

    // populate adjacency matrix with arc costs 
    for (const auto& arc : graph){
        // get the index of the two points of the arc
        int from = -1, to = -1;
        for (int i = 0; i < n; ++i){
            if (all_points[i] == arc->points[0]){
                from = i;
            }
            if (all_points[i] == arc->points[1]){
                to = i;
            }
            if (from != -1 && to != -1){
                break;
            }
        }
        if (from == -1 || to == -1){
            continue;
        }
        adj_matrix[from][to] = arc->length();
        adj_matrix[to][from] = arc->length();
    }
    return adj_matrix;
}
// perform the Dijkstra algorithm to find the shortest path
vector<Arc*> Graph::find_shortest_path() 
{
    int n = all_points.size();
    vector<vector<double>> adj_matrix = build_adjacency_matrix();

    // Dijkstra algorithm
    vector<double> dist(n, INF);
    vector<int> pred(n, -1); 
    vector<bool> visited(n, false);
    visited[0] = true;
    dist[0] = 0;

    // initialize the distance and predecessor vectors
    for (int i = 0; i < n; ++i){
        dist[i] = adj_matrix[0][i];
        pred[i] = 0;
        if (i > 1 && adj_matrix[0][i] < INF){
            pred[i] = 0;
        }
    }
    /*
    cout << "Initial distance vector: ";
    for (int i = 0; i < n; ++i){
        cout << dist[i] << " ";
    }
    cout << endl;
    */

    // apply the algorithm
    for (int i = 0; i < n; ++i){
        // find the next point to visit (the one with the smallest distance)
        double min_dist = INF;
        int next = -1;
        for (int j = 0; j < n; ++j){
            if (!visited[j] && dist[j] < min_dist){
                min_dist = dist[j];
                next = j;
            }
        }
        if (next == -1){
            break;
        }
        visited[next] = true;

        // for each successor of the next point, update the distance and predecessor vectors
        for (int j = 0; j < n; ++j){
            if (dist[j] > dist[next] + adj_matrix[next][j]){
                dist[j] = dist[next] + adj_matrix[next][j];
                pred[j] = next;
            }
        }
        /*
        cout << "Current distance vector << " << i << " >>: ";
        for (int i = 0; i < n; ++i){
            cout << dist[i] << " ";
        }
        cout << endl;
        cout << "Current predecessor vector << " << i << " >>: ";
        for (int i = 0; i < n; ++i){
            cout << i << " : " << pred[i] << ", ";
        }
        cout << endl;
        */
    }
    
    // getting all the predecessors to build the path
    int current = 1;
    vector<int> path;
    while (current != 0){
        path.push_back(current);
        current = pred[current];
    }
    path.push_back(0);
    reverse(path.begin(), path.end());
    vector<Arc*> shortest_path;
    // creating the shortest path with the arcs
    for (int i = 0; i < path.size() - 1; ++i){
        for (const auto& arc : graph){
            if ((arc->points[0] == all_points[path[i]] && arc->points[1] == all_points[path[i + 1]]) || (arc->points[0] == all_points[path[i + 1]] && arc->points[1] == all_points[path[i]])){
                shortest_path.push_back(arc);
                break;
            }
        }
    }
    return shortest_path;
}
// export the graph in a file
void Graph::exporte(const string& filename)
{
    ofstream out(filename);
    out<<"graph representation : "<<endl;
    out<<"start point : "<<start<<endl;
    out<<"goal point : "<<goal<<endl;
    if (moving_piece.arcs.size() > 0){
        out<<"moving piece : "<<endl;
        moving_piece.exporte(out);
    }
    out<<"obstacles : "<<endl;
    for (auto obs : obstacles){
        out<<"new obstacle : "<<endl;
        obs.exporte(out);
    }
    out<<"all points : "<<endl;
    for (auto point : all_points){
        out<<point<<endl;
    }
    out<<"graph arcs : "<<endl;
    for (auto arc : graph){
        out<<*arc<<endl;
    }
    out.close();
}
// find the shortest path and export it in a file
void Graph::find_shortest_path_and_exporte(const string& filename)
{
    vector<Arc*> shortest_path = find_shortest_path();
    double shortest_path_length = 0;
    for (const auto& arc : shortest_path){
        shortest_path_length += arc->length();
    }
    ofstream out(filename);
    out<<"shortest path : "<<endl;
    for (const auto& arc : shortest_path){
        out<<*arc<<endl;
    }
    out<<"shortest path length : "<<shortest_path_length<<endl;
    out.close();
}
