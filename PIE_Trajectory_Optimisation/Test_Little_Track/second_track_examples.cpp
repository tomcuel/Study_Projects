#include "../Graph_Src/graph_class.hpp"


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

    // Assemble the obstacles
    vector<Obstacle> obstacles_1 = {obstacle_1, obstacle_2};

    // Create the start and goal points
    Point start(-0.5, 0);
    Point goal(3.5, 5);

/* a bit too long for me to want to wait for the result
    // Create the graph
    Graph graph_1(obstacles_1, start, goal, false);
    // Export the graph
    string graph_1_filename = "Results/graph_5_inside_outside_layout.txt";
    graph_1.exporte(graph_1_filename);
    // find the shortest path
    graph_1.find_shortest_path_and_exporte("Results/path_5_inside_outside_layout.txt");
*/

// Test for 2 obstacles, one surrounding the track and the other in the middle, and a separation between the start and the goal to force the loop
    // new start and goal points
    Point new_start(-0.5, 2);
    Point new_goal(-0.5, 0);

    // Create the middle path from the start to the goal
    Point p15(0.5, 5);
    Point p16(4, 5.5);
    Point p17(6.5, 3);
    Point p18(-0.5, -0.5);
    Segment s15(new_start, p15);
    Segment s16(p15, p16);
    Segment s17(p16, p17);
    Segment s18(p17, p18);
    Segment s19(p18, new_goal);
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

    // Create the graph
    Graph graph_2(obstacle_1, obstacle_2, obstacle_3, middle_path_1, new_start, new_goal);
    // Export the graph
    string graph_2_filename = "Results/graph_6_inside_outside_layout.txt";
    graph_2.exporte(graph_2_filename);
    // find the shortest path
    graph_2.find_shortest_path_and_exporte("Results/path_6_inside_outside_layout.txt");


    return 0;
}
