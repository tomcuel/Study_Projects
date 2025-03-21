#include "../Graph_Src/graph_class.hpp"


int main() 
{
// Test for obstacles surrounding the track
    // Create the obstacle at the center
    Point p1(1, 1);
    Point p2(1, -1);
    Point p3(-1, -1);
    Point p4(-1, 1);
    Segment s1(p1, p2);
    Segment s2(p2, p3);
    Segment s3(p3, p4);
    Segment s4(p4, p1);
    vector<Arc*> obstacle_arcs_1 = {&s1, &s2, &s3, &s4};
    Obstacle obstacle_1(obstacle_arcs_1);

    // Create the obstacle on the right
    Point p5(2, 2);
    Point p6(4, 2);
    Point p7(4, -2);
    Point p8(2, -2);
    Segment s5(p5, p6);
    Segment s6(p6, p7);
    Segment s7(p7, p8);
    Segment s8(p8, p5);
    vector<Arc*> obstacle_arcs_2 = {&s5, &s6, &s7, &s8};
    Obstacle obstacle_2(obstacle_arcs_2);

    // Create the obstacle on the left
    Point p9(-2, 2);
    Point p10(-4, 2);
    Point p11(-4, -2);
    Point p12(-2, -2);
    Segment s9(p9, p10);
    Segment s10(p10, p11);
    Segment s11(p11, p12);
    Segment s12(p12, p9);
    vector<Arc*> obstacle_arcs_3 = {&s9, &s10, &s11, &s12};
    Obstacle obstacle_3(obstacle_arcs_3);

    // Create the obstacle on the top
    Point p13(3, 2);
    Point p14(3, 4);
    Point p15(-3, 4);
    Point p16(-3, 2);
    Segment s13(p13, p14);
    Segment s14(p14, p15);
    Segment s15(p15, p16);
    Segment s16(p16, p13);
    vector<Arc*> obstacle_arcs_4 = {&s13, &s14, &s15, &s16};
    Obstacle obstacle_4(obstacle_arcs_4);

    // Create the obstacle on the bottom
    Point p17(3, -2);
    Point p18(3, -4);
    Point p19(-3, -4);
    Point p20(-3, -2);
    Segment s17(p17, p18);
    Segment s18(p18, p19);
    Segment s19(p19, p20);
    Segment s20(p20, p17);
    vector<Arc*> obstacle_arcs_5 = {&s17, &s18, &s19, &s20};
    Obstacle obstacle_5(obstacle_arcs_5);

    // Assemble the obstacles
    vector<Obstacle> obstacles_1 = {obstacle_1, obstacle_2, obstacle_3, obstacle_4, obstacle_5};

    // Create the start and goal points
    Point start(-1.5, 1.5);
    Point goal(1.5, -1.5);

    // Create the graph
    Graph graph_1(obstacles_1, start, goal, false);
    // Export the graph
    string graph_1_filename = "Results/graph_1_surrounding_obstacles.txt";
    graph_1.exporte(graph_1_filename);
    // find the shortest path
    graph_1.find_shortest_path_and_exporte("Results/path_1_surrounding_obstacles.txt");


// Test for 2 obstacles, one surrounding the track and the other in the middle
    // Create the obstacle at the center
    // already created above

    // Create the obstacle surrounding the track
    Point p21(2, 2);
    Point p22(2, -2);
    Point p23(-2, -2);
    Point p24(-2, 2);
    Segment s21(p21, p22);
    Segment s22(p22, p23);
    Segment s23(p23, p24);
    Segment s24(p24, p21);
    vector<Arc*> obstacle_arcs_6 = {&s21, &s22, &s23, &s24};
    Obstacle obstacle_6(obstacle_arcs_6);

    // Assemble the obstacles
    vector<Obstacle> obstacles_2 = {obstacle_1, obstacle_6};

    // Create the graph
    Graph graph_2(obstacles_2, start, goal, true);
    // Export the graph
    string graph_2_filename = "Results/graph_2_borders.txt";
    graph_2.exporte(graph_2_filename);
    // find the shortest path
    graph_2.find_shortest_path_and_exporte("Results/path_2_borders.txt");


// Test for 2 obstacles, one surrounding the track and the other in the middle, and a separation between the start and the goal to force the loop
    // Create the obstacle surrounding the track
    Point p25(2, 2);
    Point p26(2, -2);
    Point p27(-2, -2);
    Point p28(-2, -0.5);
    Point p29(-2, 0.5);
    Point p30(-2, 2);
    Segment s25(p25, p26);
    Segment s26(p26, p27);
    Segment s27(p27, p28);
    Segment s28(p28, p29);
    Segment s29(p29, p30);
    Segment s30(p30, p25);
    vector<Arc*> obstacle_arcs_7 = {&s25, &s26, &s27, &s28, &s29, &s30};
    Obstacle obstacle_7(obstacle_arcs_7);
    
    // Create the obstacle at the center
    Point p31(1,1);
    Point p32(1,-1);
    Point p33(-1,-1);
    Point p34(-1,-0.5);
    Point p35(-1,0.5);
    Point p36(-1,1);
    Segment s31(p31, p32);
    Segment s32(p32, p33);
    Segment s33(p33, p34);
    Segment s34(p34, p35);
    Segment s35(p35, p36);
    Segment s36(p36, p31);
    vector<Arc*> obstacle_arcs_8 = {&s31, &s32, &s33, &s34, &s35, &s36};
    Obstacle obstacle_8(obstacle_arcs_8);

    // new start and goal points
    Point new_start(-1.5, 1);
    Point new_goal(-1.5, -1);
    
    // Create the middle path from the start to the goal
    Point p37(-1.5, 1.5);
    Point p38(1.5, 1.5);
    Point p39(1.5, -1.5);
    Point p40(-1.5, -1.5);
    Segment s37(new_start, p37);
    Segment s38(p37, p38);
    Segment s39(p38, p39);
    Segment s40(p39, p40);
    Segment s41(p40, new_goal);
    vector<Arc*> middle_path_1 = {&s37, &s38, &s39, &s40, &s41};

    // Create a rectangle obstacle in the middle to separate the start and the goal
    Point p41(-2, 0.5);
    Point p42(-1, 0.5);
    Point p43(-1, -0.5);
    Point p44(-2, -0.5);
    Segment s42(p41, p42);
    Segment s43(p42, p43);
    Segment s44(p43, p44);
    Segment s45(p44, p41);
    vector<Arc*> obstacle_arcs_9= {&s42, &s43, &s44, &s45};
    Obstacle obstacle_9(obstacle_arcs_9);

    // Create the graph, using the newly created method
    Graph graph_3(obstacle_7, obstacle_8, obstacle_9, middle_path_1, new_start, new_goal);
    string graph_3_filename = "Results/graph_3_borders_start_finish_separation_next.txt";
    graph_3.exporte(graph_3_filename);
    // find the shortest path
    graph_3.find_shortest_path_and_exporte("Results/path_3_borders_start_finish_separation_next.txt");
  

// Test for 2 obstacles, one surrounding the track and the other in the middle, and a separation between the start and the goal to force the loop
// here the separation is creating overlapping obstacles, and it doesn't work anymore
    // Create the obstacle at the center
    // already created above

    // Create the obstacle surrounding the track
    // already created above

    // Create a rectangle obstacle in the middle to separate the start and the goal
    Point p45(-2.5, 0.5);
    Point p46(-0.5, 0.5);
    Point p47(-0.5, -0.5);
    Point p48(-2.5, -0.5);
    Segment s46(p45, p46);
    Segment s47(p46, p47);
    Segment s48(p47, p48);
    Segment s49(p48, p45);
    vector<Arc*> obstacle_arcs_10 = {&s46, &s47, &s48, &s49};
    Obstacle obstacle_10(obstacle_arcs_10);

    // Assemble the obstacles
    vector<Obstacle> obstacles_3 = {obstacle_1, obstacle_7};

    // same start and goal points as before

    // Create the graph
    Graph graph_4(obstacles_3, new_start, new_goal, false);
    // Add the rectangle obstacle that separates the start and the goal
    graph_4.add_obstacle(obstacle_10);
    // Export the graph
    string graph_4_filename = "Results/graph_4_borders_start_finish_separation_overlapping.txt";
    graph_4.exporte(graph_4_filename);
    // find the shortest path
    graph_4.find_shortest_path_and_exporte("Results/path_4_borders_start_finish_separation_overlapping.txt");
  

    return 0;
}
