#include "../Src/point_classe.hpp"


int main()
{
    // Test 1D
    Point P1(3);
    cout<<"P1="<<P1<<endl;
    Point P2=P1+P1; // Adding two points
    cout<<"P2="<<P2<<endl;
    cout<<"Norm of P2 = "<<norme(P2)<<endl;
    Point P3(6);
    cout<<"P3 = "<<P3<<endl;
    cout<<"Measure of 'triangle' (1D) = "<<mesure(P1, P2, P3)<<endl;


    // Test 2D
    Point P4(3,5);
    cout<<"\nP1="<<P4<<endl;
    Point P5 =P4+P4;
    cout<<"P5="<<P5<<endl;
    cout<<"norme P5="<<norme(P5)<<endl;
    Point P6(6,5);
    cout<<"P6="<<P6<<endl;
    cout<<"Aire triangle = "<<mesure(P4, P5, P6)<<endl;
    cout<<"\n";


    return 0;
}