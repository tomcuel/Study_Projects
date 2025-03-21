#ifndef __GRAPH_CLASS_HPP__
#define __GRAPH_CLASS_HPP__


#include "obstacle_class.hpp"
#include <set>
#include <limits>
const double INF = numeric_limits<double>::infinity();


//==========================================================================
// class Graph : to setup the graph of the problem
//==========================================================================
class Graph
{
public:
    vector<Obstacle> obstacles; // list of obstacles
    Point start, goal; // start and goal points
    Obstacle moving_piece; // moving obstacle (start point = barycenter of the moving piece)
    vector<Point> all_points; // list of all points in the graph
    vector<Arc*> graph; // graph of the problem

    // constructors
    Graph(const Point& s, const Point& g); // with only start and goal points
    Graph(const vector<Obstacle>& obs, const Point& s, const Point& g, bool are_obstacles_outer_and_inside_layout); // with obstacles, start and goal points
    Graph(const Obstacle& outer_track, const Obstacle& inside_track, const Obstacle& linking_obstacle, vector<Arc*> middle_path, const Point& s, const Point& g); // with the outer track, the inner track, the linking obstacle and the middle path (track center)
    Graph(const vector<Obstacle>& obs, const Point& g, const Obstacle& mv_p, bool are_obstacles_outer_and_inside_layout); // with obstacles, goal point, and a moving piece (that is the start point), things are different if obstacles are only the outer and inner layout of the track

    void add_obstacle(const Obstacle& ob); // add an obstacle to the graph and modify it if necessary
    void apply_padding_to_obstacles(); // apply padding to the obstacles in case of a moving piece (2D not only a point)

    vector<vector<double>> build_adjacency_matrix(); // build the adjacency matrix for the graph
    vector<Arc*> find_shortest_path(); // perform the Dijkstra algorithm to find the shortest path

    void exporte(const string& filename); // export the graph in a file
    void find_shortest_path_and_exporte(const string& filename); // find the shortest path and export it in a file

};
//==========================================================================



#endif // __GRAPH_CLASS_HPP__