#include <iostream>

int main ()
{
    system("./first_track_examples.x");
    system("./second_track_examples.x");
    system("./multi_point_track_examples.x");
    system("python3 plot_results.py");

    return 0;
}