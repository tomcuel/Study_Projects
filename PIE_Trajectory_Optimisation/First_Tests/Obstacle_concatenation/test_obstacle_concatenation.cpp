#include "../../Graph_Src/graph_class.hpp"


int main() 
{
    // create a first obstacle
    Point p1(0, 0);
    Point p2(0, 2);
    Point p3(2, 2);
    Point p4(2, 0);
    Segment s1(p1, p2);
    Segment s2(p2, p3);
    Segment s3(p3, p4);
    Segment s4(p4, p1);
    vector<Arc*> obstacle_arcs_1 = {&s1, &s2, &s3, &s4};
    Obstacle obstacle_1(obstacle_arcs_1);


    // Testing if a point is inside the obstacle 
    // fully inside
    Point p5(1, 1);
    // fully outside
    Point p6(4, 4);
    // on a summit
    Point p7(2, 2);
    // on a side
    Point p8(1, 2);
    // testing the function
    cout << "testing if a point is inside the obstacle" << endl;
    cout << "fully inside point : is inside ? " << (is_inside(p5, obstacle_1) ? "true" : "false") << endl;
    cout << "fully outside point : is inside ? " << (is_inside(p6, obstacle_1) ? "true" : "false") << endl;
    cout << "on a summit point : is inside ? " << (is_inside(p7, obstacle_1) ? "true" : "false") << endl;
    cout << "on a side point : is inside ? " << (is_inside(p8, obstacle_1) ? "true" : "false") << endl;
    // Result : only when fully inside the obstacle, the point is inside the obstacle
    cout << endl;


    // Testing if the two segment intersect to see wether it can be on extremities
    Segment s5(Point(0, 1), Point(0, 2));
    // fully separated segment
    Segment s6(Point(1, 0), Point(2, 0));
    // overlapping segment
    Segment s7(Point(0, 0), Point(0, 3));
    // intersecting segment
    Segment s8(Point(-1, 1.5), Point(1, 1.5));
    // intersecting segment only on one extremity
    Segment s9(Point(0, 1), Point(1, 1.5));
    // intersecting segment only on one point
    Segment s10(Point(-1, 1.5), Point(0, 1.5));
    // testing the function
    cout << "testing if two segments intersect" << endl;
    cout << "fully separated segment : do they intersect ? " << (do_segments_intersect(s5, s6) ? "true" : "false") << endl;
    cout << "overlapping segment : do they intersect ? " << (do_segments_intersect(s5, s7) ? "true" : "false") << endl;
    cout << "intersecting segment : do they intersect ? " << (do_segments_intersect(s5, s8) ? "true" : "false") << endl;
    cout << "intersecting segment only on one extremity : do they intersect ? " << (do_segments_intersect(s5, s9) ? "true" : "false") << endl;
    cout << "intersecting segment only on one point : do they intersect ? " << (do_segments_intersect(s5, s10) ? "true" : "false") << endl;
    // Result : only when the two segments are intersecting not on an extremity and without overlapping, the function returns true to the segments intersecting
    cout << endl;
    

    // Testing if two obstacles intersect
    // create a second obstacle that is intersecting the first one
    Point p9(1, 1);
    Point p10(1, 3);
    Point p11(3, 3);
    Point p12(3, 1);
    Segment s11(p9, p10);
    Segment s12(p10, p11);
    Segment s13(p11, p12);
    Segment s14(p12, p9);
    vector<Arc*> obstacle_arcs_2 = {&s11, &s12, &s13, &s14};
    Obstacle obstacle_2(obstacle_arcs_2);
    // create a third obstacle that is not intersecting the first one
    Point p13(4, 4);
    Point p14(4, 6);
    Point p15(6, 6);
    Point p16(6, 4);
    Segment s15(p13, p14);
    Segment s16(p14, p15);
    Segment s17(p15, p16);
    Segment s18(p16, p13);
    vector<Arc*> obstacle_arcs_3 = {&s15, &s16, &s17, &s18};
    Obstacle obstacle_3(obstacle_arcs_3);
    // create a fourth obstacle that is fully inside the first one
    Point p17(0.5, 0.5);
    Point p18(0.5, 1.5);
    Point p19(1.5, 1.5);
    Point p20(1.5, 0.5);
    Segment s19(p17, p18);
    Segment s20(p18, p19);
    Segment s21(p19, p20);
    Segment s22(p20, p17);
    vector<Arc*> obstacle_arcs_4 = {&s19, &s20, &s21, &s22};
    Obstacle obstacle_4(obstacle_arcs_4);
    // create a fifth obstacle that is side by side with the first one
    Point p21(2, 0);
    Point p22(2, 2);
    Point p23(4, 2);
    Point p24(4, 0);
    Segment s23(p21, p22);
    Segment s24(p22, p23);
    Segment s25(p23, p24);
    Segment s26(p24, p21);
    vector<Arc*> obstacle_arcs_5 = {&s23, &s24, &s25, &s26};
    Obstacle obstacle_5(obstacle_arcs_5);
    // create a sixth obstacle that is fully inside but with common sides with the first one and no stricly inside points
    Point p25(0, 0);
    Point p26(0, 1);
    Point p27(2, 1);
    Point p28(2, 0);
    Segment s27(p25, p26);
    Segment s28(p26, p27);
    Segment s29(p27, p28);
    Segment s30(p28, p25);
    vector<Arc*> obstacle_arcs_6 = {&s27, &s28, &s29, &s30};
    Obstacle obstacle_6(obstacle_arcs_6);
    // create a seventh obstacle that is on the side of the first one but with no common points
    Point p29(2, 3);
    Point p30(3, 3);
    Point p31(3, -1);
    Point p32(2, -1);
    Segment s31(p29, p30);
    Segment s32(p30, p31);
    Segment s33(p31, p32);
    Segment s34(p32, p29);
    vector<Arc*> obstacle_arcs_7 = {&s31, &s32, &s33, &s34};
    Obstacle obstacle_7(obstacle_arcs_7);
    // testing the function
    cout << "testing if two obstacles intersect" << endl;
    cout << "intersecting obstacle : do they intersect ? " << (do_obstacles_intersect(obstacle_1, obstacle_2) ? "true" : "false") << endl;
    cout << "non intersecting obstacle : do they intersect ? " << (do_obstacles_intersect(obstacle_1, obstacle_3) ? "true" : "false") << endl;
    cout << "fully inside obstacle : do they intersect ? " << (do_obstacles_intersect(obstacle_1, obstacle_4) ? "true" : "false") << endl;
    cout << "side by side obstacle : do they intersect ? " << (do_obstacles_intersect(obstacle_1, obstacle_5) ? "true" : "false") << endl;
    cout << "fully inside with common sides obstacle : do they intersect ? " << (do_obstacles_intersect(obstacle_1, obstacle_6) ? "true" : "false") << endl;
    cout << "on the side with no common points obstacle : do they intersect ? " << (do_obstacles_intersect(obstacle_1, obstacle_7) ? "true" : "false") << endl;
    // Result : obstacles intersect when they have at least one point strictly inside the other obstacle (side by side is not enough)
    cout << endl;


    // Try to concatenate the two obstacles into a single one
    // first : obstacle1 and obstacle2 : they intersect since they are overlapping squares
    Obstacle obstacle_8 = concatenate_obstacles(obstacle_1, obstacle_2);
    // export the concatenated obstacle
    ofstream concatenated_file_1("concatenated_obstacle_1.txt");
    obstacle_8.exporte(concatenated_file_1);
    concatenated_file_1.close();


    // creating a second obstacle to test with the first one
    Point p33(1, 1);
    Point p34(3, 1);
    Point p35(3, 3);
    Segment s35(p33, p34);
    Segment s36(p34, p35);
    Segment s37(p35, p33);
    vector<Arc*> obstacle_arcs_9 = {&s35, &s36, &s37};
    Obstacle obstacle_9(obstacle_arcs_9);
    // second : obstacle1 and obstacle9 : they intersect since they are a square and a triangle overlapping
    Obstacle obstacle_10 = concatenate_obstacles(obstacle_1, obstacle_9);
    // export the concatenated obstacle
    ofstream concatenated_file_2("concatenated_obstacle_2.txt");
    obstacle_10.exporte(concatenated_file_2);
    concatenated_file_2.close();


    // it does work for such simple cases, but it is not enough to concatenate obstacles that have common sides but no strictly inside points for examples
    // we will make sure afterwards that we don't have obstacles that are overlapping
    return 0;
}