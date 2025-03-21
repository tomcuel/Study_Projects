#include "../Graph_Src/graph_class.hpp"
#include <chrono>


// function to subdivide a single arc into n smaller arcs
vector<Arc*> subdivideArc(Arc* arc, int n)
{
    const Segment* seg = dynamic_cast<Segment*>(arc);
    vector<Arc*> sub_arcs;
    double dx = (seg->points[1].x - seg->points[0].x) / n;
    double dy = (seg->points[1].y - seg->points[0].y) / n;

    Point prev(seg->points[0].x, seg->points[0].y);
    for (int i = 1; i <= n; ++i){
        Point next(seg->points[0].x + i * dx, seg->points[0].y + i * dy);
        sub_arcs.push_back(new Segment(prev, next));
        prev = next;
    }
    return sub_arcs;
}
// function to subdivide a single obstacle into smaller arcs
// the without is just for the sake of this example, to avoid subdividing the arcs at the place where the separation is
Obstacle subdivideObstacles(const Obstacle& obstacle, int n, int index_without)
{
    vector<Arc*> new_segments;  // Store all subdivided arcs
    int index = 0; 
    for (Arc* arc : obstacle.arcs){
        if (index == index_without){
            new_segments.push_back(arc);
            continue;
        }
        index++;
        vector<Arc*> sub_arcs = subdivideArc(arc, n);
        new_segments.insert(new_segments.end(), sub_arcs.begin(), sub_arcs.end());
    }
    return Obstacle(new_segments);
}


int main() 
{
// Test for 2 obstacles, one surrounding the track and the other in the middle
    // Create the obstacle at the center
    Point p1(0, 0);
    Point p2(6, 3);
    Point p3(3, 5);
    Point p4(1, 5);
    Point p5(0, 2);
    Point p6(0, 1.5);
    Point p7(0, 0.5);
    Segment s1(p1, p2);
    Segment s2(p2, p3);
    Segment s3(p3, p4);
    Segment s4(p4, p5);
    Segment s5(p5, p6);
    Segment s6(p6, p7);
    Segment s7(p7, p1);
    vector<Arc*> obstacle_arcs_1 = {&s1, &s2, &s3, &s4, &s5, &s6, &s7};
    Obstacle obstacle_1(obstacle_arcs_1);

    // Create the obstacle surrounding the track
    Point p8(-1, -1);
    Point p9(7, 3);
    Point p10(4, 6);
    Point p11(0, 5);
    Point p12(-1, 2);
    Point p13(-1, 1.5);
    Point p14(-1, 0.5);
    Segment s8(p8, p9);
    Segment s9(p9, p10);
    Segment s10(p10, p11);
    Segment s11(p11, p12);
    Segment s12(p12, p13);
    Segment s13(p13, p14);
    Segment s14(p14, p8);
    vector<Arc*> obstacle_arcs_2 = {&s8, &s9, &s10, &s11, &s12, &s13, &s14};
    Obstacle obstacle_2(obstacle_arcs_2);

    // Subdivide the obstacles into smaller arcs (n = 5)
    Obstacle sub_inside_track = subdivideObstacles(obstacle_1, 5, 5);
    Obstacle sub_outside_track = subdivideObstacles(obstacle_2, 5, 5);

    // Create the start and goal points
    Point start(-0.5, 2);
    Point goal(-0.5, 0);

    // Create the middle path from the start to the goal
    Point p15(0.5, 5);
    Point p16(4, 5.5);
    Point p17(6.5, 3);
    Point p18(-0.5, -0.5);
    Segment s15(start, p15);
    Segment s16(p15, p16);
    Segment s17(p16, p17);
    Segment s18(p17, p18);
    Segment s19(p18, goal);
    vector<Arc*> middle_path_1 = {&s15, &s16, &s17, &s18, &s19};

    // Create the obstacle to separate the start and the goal
    Point p19(-1, 1.5);
    Point p20(0, 1.5);
    Point p21(0, 0.5);
    Point p22(-1, 0.5);
    Segment s20(p19, p20);
    Segment s21(p20, p21);
    Segment s22(p21, p22);
    Segment s23(p22, p19);
    vector<Arc*> obstacle_arcs_3 = {&s20, &s21, &s22, &s23};
    Obstacle obstacle_3(obstacle_arcs_3);

    // Create the graph with timing
    std::cout << "Creating the graph..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    Graph graph(sub_outside_track, sub_inside_track, obstacle_3, middle_path_1, start, goal);
    auto end_time = std::chrono::high_resolution_clock::now();
    double graph_creation_time = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "Graph created in " << graph_creation_time << " seconds." << std::endl;

    // Export the graph
    string graph_filename = "Results/graph_7_subdivided_obstacles.txt";
    graph.exporte(graph_filename);

    // Find the shortest path with timing
    std::cout << "Finding the shortest path..." << std::endl;
    start_time = std::chrono::high_resolution_clock::now();
    graph.find_shortest_path_and_exporte("Results/path_7_subdivided_obstacles.txt");
    end_time = std::chrono::high_resolution_clock::now();
    double shortest_path_time = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "Shortest path found in " << shortest_path_time << " seconds." << std::endl;


    return 0;
}
