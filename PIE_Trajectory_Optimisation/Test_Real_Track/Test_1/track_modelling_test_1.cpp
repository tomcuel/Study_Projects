#include "../../Graph_Src/graph_class.hpp"
#include <cstdlib>
#include <map>
#include <sstream>


// function to get the track data from a csv file
std::map<int, std::vector<double>> get_track_data(std::string file_name)
{
    std::map<int, std::vector<double>> track_data;

    std::ifstream file(file_name);
    // ensure file is open
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << file_name << std::endl;
        return track_data; // return empty map
    }

    std::string line;
    int i = 0;
    std::getline(file, line); // skip header row
    // read data, line by line
    while (std::getline(file, line))
    {
        // for each line, get the data
        std::vector<double> data;
        std::stringstream line_stream(line);
        std::string cell;
        std::getline(line_stream, cell, ','); // skip first column since it is the index
        while (std::getline(line_stream, cell, ','))
        {
            data.push_back(std::stod(cell));
        }
        track_data[i] = data;
        i++;
    }
    return track_data;
}
// function to compute the inside and outside points of a track segment based on the track direction
std::pair<Point, Point> compute_inside_outside(const Point& prev, const Point& current, const Point& next, double distance_from_track_center) {
    // compute direction vectors
    Point d1(current.x - prev.x, current.y - prev.y);
    Point d2(next.x - current.x, next.y - current.y);

    // normalize directions
    Point d1_norm = normalize(d1);
    Point d2_norm = normalize(d2);

    //cCompute approximate bisector
    Point bisector(d1_norm.x + d2_norm.x, d1_norm.y + d2_norm.y);
    bisector = normalize(bisector);

    // compute perpendicular direction
    Point n(-bisector.y, bisector.x);

    // compute inside and outside points (distance_from_track_center meters offset)
    Point p_in(current.x - distance_from_track_center * n.x, current.y - distance_from_track_center * n.y);
    Point p_out(current.x + distance_from_track_center * n.x, current.y + distance_from_track_center * n.y);

    // determine which is inside and which is outside
    Point track_dir(next.x - current.x, next.y - current.y);
    double cross = track_dir.x * n.y - track_dir.y * n.x; // cross product
    if (cross < 0) { 
        std::swap(p_in, p_out); 
    }

    return make_pair(p_in, p_out);
}


int main ()
{
    // precomputing the csv file, that is a python script, so using system command
    double distance_from_track_center = 1.0;

    // the goal from there is to create obstacles that represent the track borders
    // the vehicle will first be placed at the start point, and the goal will be the end point
    // after that, we will try to modelize the vehicle as a 2x1 rectangle and use the padding to get the same results
    // we need to modelize the track as a set of obstacles that are rectangles that we concatenate

    // we first get the track data centered in meters 
    std::map<int, std::vector<double>> track_data = get_track_data("track_data_centered_test_1.csv");

    // for each point in the track data, we need to get an inside and outside point that are 4 meters away from the center
    // for each, we need to get the bissectrice of the angle between the points and the one before and after and get the two points that are 4 meters away from the center
    // one will go into the outside point set and the other in the inside point set
    vector<Point> inside_points;
    vector<Point> outside_points;
    for (int i = 1; i < track_data.size()-1; i++){
        Point prev(track_data[i-1][1], track_data[i-1][2]);
        Point current(track_data[i][1], track_data[i][2]);
        Point next(track_data[i+1][1], track_data[i+1][2]);

        std::pair<Point, Point> in_out = compute_inside_outside(prev, current, next, distance_from_track_center);
        inside_points.push_back(in_out.first);
        outside_points.push_back(in_out.second);
    }
    // add the outside and inside points of the first and last points
    // last point
    Point prev(track_data[track_data.size()-2][1], track_data[track_data.size()-2][2]);
    Point current(track_data[track_data.size()-1][1], track_data[track_data.size()-1][2]);
    Point next(track_data[0][1], track_data[0][2]);
    std::pair<Point, Point>  in_out_first_last = compute_inside_outside(prev, current, next, distance_from_track_center);
    inside_points.push_back(in_out_first_last.first);
    outside_points.push_back(in_out_first_last.second);
    // first point
    prev = Point(track_data[track_data.size()-1][1], track_data[track_data.size()-1][2]);
    current = Point(track_data[0][1], track_data[0][2]);
    next = Point(track_data[1][1], track_data[1][2]);
    in_out_first_last = compute_inside_outside(prev, current, next, distance_from_track_center);
    inside_points.push_back(in_out_first_last.first);
    outside_points.push_back(in_out_first_last.second);

    // creating the obstacles : inside and outside track layout
    vector<Arc*> outside_track;
    vector<Arc*> inside_track;
    for (int i = 0; i < inside_points.size()-1; i++){
        inside_track.push_back(new Segment(inside_points[i], inside_points[i+1]));
        outside_track.push_back(new Segment(outside_points[i], outside_points[i+1]));
    }
    // add the last segment
    inside_track.push_back(new Segment(inside_points[inside_points.size()-1], inside_points[0]));
    outside_track.push_back(new Segment(outside_points[outside_points.size()-1], outside_points[0]));

    // saving the obstacles in a file to be used in the python script to plot the results
    std::ofstream inside_track_file("inside_track_1.txt");
    std::ofstream outside_track_file("outside_track_1.txt");
    for (const auto& arc : inside_track){
        inside_track_file << arc->points[0].x << "," << arc->points[0].y << endl;
    }
    inside_track_file << inside_track[inside_track.size()-1]->points[1].x << "," << inside_track[inside_track.size()-1]->points[1].y << endl;
    for (const auto& arc : outside_track){
        outside_track_file << arc->points[0].x << "," << arc->points[0].y << endl;
    }
    outside_track_file << outside_track[outside_track.size()-1]->points[1].x << "," << outside_track[outside_track.size()-1]->points[1].y << endl;

    // creating the graph
    Obstacle outside_obstacle(outside_track);
    Obstacle inside_obstacle(inside_track);
    vector<Obstacle> obstacles = {outside_obstacle, inside_obstacle};
    Point start(-1, 0);
    Point goal(2, 1);
    Graph graph(obstacles, start, goal, false);

    // creating the start and finish separator
    Segment seg1(inside_points[0], inside_points[inside_points.size()-1]);
    Segment seg2(inside_points[inside_points.size()-1], outside_points[outside_points.size()-1]);
    Segment seg3(outside_points[outside_points.size()-1], outside_points[0]);
    Segment seg4(outside_points[0], inside_points[0]);
    vector<Arc*> start_finish_separator = {&seg1, &seg2, &seg3, &seg4}; 
    Obstacle start_finish_obstacle(start_finish_separator);
    graph.add_obstacle(start_finish_obstacle);
    graph.exporte("graph_1.txt");
    graph.find_shortest_path_and_exporte("path_1.txt");

    system("python3 test_1_results.py");
    




    return 0;
}