#include "../Graph_Src/graph_class.hpp"
#include <cstdlib>
#include <map>
#include <sstream>
#include <chrono>


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
    file.close();
    return track_data;
}
// function to get the data from the csv file containing the path to follow
vector<Point> get_path_data(std::string file_name)
{
    vector<Point> path_data;

    std::ifstream file(file_name);
    // ensure file is open
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << file_name << std::endl;
        return path_data; // return empty vector
    }

    std::string line;
    std::getline(file, line); // skip header row
    // read data, line by line
    while (std::getline(file, line))
    {
        // for each line, get the data
        std::stringstream line_stream(line);
        std::string cell;
        std::getline(line_stream, cell, ',');
        double x = std::stod(cell);
        std::getline(line_stream, cell, ',');
        double y = std::stod(cell);
        path_data.push_back(Point(x, y));
    }
    file.close();
    return path_data;
}
// function to compute the inside and outside points of a track segment based on the track direction
// give the outside and inside points based on the previous, current and next points, depending on the distance from the track center
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
    // since there are too many points, very close by, we need to cut many of them 
    int cut_by = 3;


    // precomputing the csv file, that is a python script, so using system command
    system("python3 track_data_input.py");



    // width of the track is 10m, so the distance from the center is 5m, and we consider our vehicle to be 2m wide at max (it will depend on the regulation but it will not be more than this)
    double distance_from_track_center = 4.0;



    // we first get the track data centered in meters
    std::map<int, std::vector<double>> track_data = get_track_data("Data/track_data_centered.csv");
    


    // for each point in the track data, we need to get an inside and outside point that are 4 meters away from the center
    // for each, we need to get the bissectrice of the angle between the points and the one before and after and get the two points that are 4 meters away from the center
    // one will go into the outside point set and the other in the inside point set
    vector<Point> inside_points;
    vector<Point> outside_points;
    vector<Point> track_center_points;
    for (int i = 1; i < track_data.size()-1; ++i){
        if (i % cut_by == 0){
            Point prev(track_data[i-1][1], track_data[i-1][2]);
            Point current(track_data[i][1], track_data[i][2]);
            Point next(track_data[i+1][1], track_data[i+1][2]);
            std::pair<Point, Point> in_out = compute_inside_outside(prev, current, next, distance_from_track_center);
            inside_points.push_back(in_out.first);
            outside_points.push_back(in_out.second);
            track_center_points.push_back(current);
        }
    }
    // add the outside and inside points of the first and last points (not added for the center track since it will mess up the graph)
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
    vector<Arc*> center_track;
    for (int i = 0; i < inside_points.size()-1; i++){
        inside_track.push_back(new Segment(inside_points[i], inside_points[i+1]));
        outside_track.push_back(new Segment(outside_points[i], outside_points[i+1]));
    }
    for (int i = 0; i < track_center_points.size()-1; i++){
        center_track.push_back(new Segment(track_center_points[i], track_center_points[i+1]));
    }
    // add the last segment
    inside_track.push_back(new Segment(inside_points[inside_points.size()-1], inside_points[0]));
    outside_track.push_back(new Segment(outside_points[outside_points.size()-1], outside_points[0]));
    // not adding it between the start and the end point for the center track



    // saving the obstacles in a file to be used in the python script to plot the results
    // center points
    std::ofstream track_center_file("Data/track_center_points.csv");
    track_center_file << "utm_x,utm_y" << endl;
    for (const auto& arc : center_track){
        track_center_file << arc->points[0].x << "," << arc->points[0].y << endl;
    }
    track_center_file << center_track[center_track.size()-1]->points[1].x << "," << center_track[center_track.size()-1]->points[1].y << endl;
    track_center_file.close();



    // creating the graph obstacles : inside and outside track layout
    Obstacle outside_obstacle(outside_track);
    Obstacle inside_obstacle(inside_track);

    // creating the start and goal points
    Point start(track_center_points[0].x, track_center_points[0].y);
    Point goal(track_center_points[track_center_points.size()-1].x, track_center_points[track_center_points.size()-1].y);

    // creating the start and finish separator obstacles
    // those are the last segments of the inside and outside obstacles
    Segment seg1(inside_points[inside_points.size()-1], inside_points[inside_points.size()-2]);
    Segment seg2(inside_points[inside_points.size()-2], outside_points[outside_points.size()-2]);
    Segment seg3(outside_points[outside_points.size()-2], outside_points[inside_points.size()-1]);
    Segment seg4(outside_points[inside_points.size()-1], inside_points[inside_points.size()-1]);
    vector<Arc*> start_finish_separator = {&seg1, &seg2, &seg3, &seg4}; 
    Obstacle start_finish_obstacle(start_finish_separator);

    // create the graph with timing
    std::cout << "Creating the graph..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    Graph graph(outside_obstacle, inside_obstacle, start_finish_obstacle, center_track, start, goal);
    auto end_time = std::chrono::high_resolution_clock::now();
    double graph_creation_time = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "Graph created in " << graph_creation_time << " seconds." << std::endl;
    
    // export the graph datas 
    graph.exporte("Data/graph.txt");



    // find the shortest path with timing
    std::cout << "Finding the shortest path..." << std::endl;
    start_time = std::chrono::high_resolution_clock::now();
    vector<Arc*> shortest_path = graph.find_shortest_path(); // find the shortest path and get the arcs
    end_time = std::chrono::high_resolution_clock::now();
    double shortest_path_time = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "Shortest path found in " << shortest_path_time << " seconds." << std::endl;

    // export the graph with the shortest path and get  all the points of the path
    double shortest_path_length = 0;
    vector<Point> path_points;
    for (int i = 1; i < shortest_path.size()-1; i++){
        shortest_path_length += shortest_path[i]->length();
        path_points.push_back(shortest_path[i]->points[0]);
    }
    // link the last and first points
    Segment last_first(Point(shortest_path[shortest_path.size()-2]->points[1].x, shortest_path[shortest_path.size()-2]->points[1].y), Point(shortest_path[1]->points[0].x, shortest_path[1]->points[0].y));
    shortest_path_length += last_first.length();
    path_points.push_back(last_first.points[0]);
    std::cout << "Shortest path length : " << shortest_path_length << std::endl;

    // exporting the datas
    ofstream path_file("Data/path.txt");
    path_file<<"shortest path : "<<endl;
    for (int i = 1; i < shortest_path.size()-1; i++){
        path_file<<*shortest_path[i]<<endl;
    }
    path_file<<last_first<<endl;
    path_file<<"shortest path length : "<<shortest_path_length<<endl;
    path_file.close();



    // getting the scale of the track points to make the correct conversion from utm to longitude and latitude
    // Find the min and max values for UTM and lat/long coordinates
    double utmx_min = track_data[0][1], utmx_max = track_data[0][1];
    double utmy_min = track_data[0][2], utmy_max = track_data[0][2];
    double longx_min = track_data[0][3], longx_max = track_data[0][3];
    double longy_min = track_data[0][4], longy_max = track_data[0][4];
    for (int i = 1; i < track_data.size(); i++){
        if (track_data[i][1] < utmx_min){
            utmx_min = track_data[i][1];
        }
        if (track_data[i][1] > utmx_max){
            utmx_max = track_data[i][1];
        }
        if (track_data[i][2] < utmy_min){
            utmy_min = track_data[i][2];
        }
        if (track_data[i][2] > utmy_max){
            utmy_max = track_data[i][2];
        }
        if (track_data[i][3] < longx_min){
            longx_min = track_data[i][3];
        }
        if (track_data[i][3] > longx_max){
            longx_max = track_data[i][3];
        }
        if (track_data[i][4] < longy_min){
            longy_min = track_data[i][4];
        }
        if (track_data[i][4] > longy_max){
            longy_max = track_data[i][4];
        }
    }
    // calculate scale factors
    double scale_x = (longx_max - longx_min) / (utmx_max - utmx_min);
    double scale_y = (longy_max - longy_min) / (utmy_max - utmy_min);
    // now I need to get all the evelation data for each point in the path by looking at the closest point in the track data for each point in the path
    std::ofstream path_elevation_file("Data/path.csv");
    path_elevation_file << "elevation,utm_x_norm,utm_y_norm,longx_norm,longy_norm" << endl;
    for (const auto& point : path_points){
        // getting the elevation of the closest point in the track data
        double min_distance = 1000000;
        double elevation = 0;
        for (int i = 0; i < track_data.size(); i++){
            double distance = (track_data[i][1] - point.x)*(track_data[i][1] - point.x) + (track_data[i][2] - point.y)*(track_data[i][2] - point.y);
            if (distance < min_distance){
                min_distance = distance;
                elevation = track_data[i][0];
            }
        }
        // getting the longitude and latitude of the point based on the track data ones (no offset since both are centered)
        double longitude = scale_x * point.x;
        double latitude = scale_y * point.y;

        // adding the point to the file
        path_elevation_file << elevation << "," << point.x << "," << point.y << "," << longitude << "," << latitude << endl;
    }
    path_elevation_file.close();



    // creates some visuals
    // export the data in a proper csv file, so the vehicle knows where to go
    system("python3 track_data_output.py");



    // getting a track data that have points at each meters if not direction changes 
    system("python3 continuous_track_data.py");



    // cleaning the executable files when quitting
    // system("make realclean"); */



    return EXIT_SUCCESS;
}