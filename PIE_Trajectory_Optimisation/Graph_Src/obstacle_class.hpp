//==========================================================================
// file defining the obstacle class
//==========================================================================
#ifndef __OBSTACLE_CLASS_HPP__
#define __OBSTACLE_CLASS_HPP__


#include "arc_class.hpp"
using namespace std;



//==========================================================================
// class Obstacle : polygonal obstacle
//==========================================================================
class Obstacle
{
public : 
    vector<Arc*> arcs; // obstacle arcs (side of the polygon)

    // constructors
    Obstacle(); // empty obstacle
    Obstacle(const vector<Arc*>& sides); // obstacle with the list of sides and their properties

    void apply_padding(double padding_distance, bool is_reversed = false); // apply padding to the obstacle
    void exporte(ostream& out); // export the obstacle in a file
};
//==========================================================================
// check if a point is stricly inside the obstacle
bool is_inside(const Point& P, const Obstacle& obstacle);
// check if the arc intersects the obstacle
bool does_arc_intersect_obstacle(const Arc& arc, const Obstacle& obstacle);
// check if the two obstacles intersect
bool do_obstacles_intersect(const Obstacle& obstacle1, const Obstacle& obstacle2);
// barycentre of the obstacle (only for polygonal obstacles for now) and update the points (vertices) of the obstacle
Point barycenter(const Obstacle& obstacle);
// obstacle area (only for polygonal obstacles for now)
double area(const Obstacle& obstacle);
// create an obstacle out of two obstacles that intersect (we know that they intersect before calling this function)
Obstacle concatenate_obstacles(const Obstacle& obstacle1, const Obstacle& obstacle2);


#endif // __OBSTACLE_CLASS_HPP__