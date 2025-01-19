#include "../Src/elements_finis_classe.hpp"


int main()
{
    // pour un segment : EF1D
    EF1D ef1d;
    Matrice M1(2,2), K1(2,2);
    Vecteur_Points P1_1D = {Point(0,0), Point(1,0)};
    ef1d.masseP1_elem(P1_1D, M1);
    ef1d.rigidP1_elem(P1_1D, K1);
    cout<<"Points du segment : "<<P1_1D[0]<<" et "<<P1_1D[1]<<endl;
    cout<<"Matrice de masse élémentaire pour un segment : ";
    cout<<M1<<endl;
    cout<<"Matrice de rigidité élémentaire pour un segment : ";
    cout<<K1<<endl;
    cout<<"\n";


    // pour un triangle : EF2D
    EF2D ef2d;
    Matrice M2(3,3), K2(3,3);
    Vecteur_Points P1_2D = {Point(0,0), Point(1,0), Point(0,1)};
    cout<<"Points du triangle : "<<P1_2D[0]<<", "<<P1_2D[1]<<" et "<<P1_2D[2]<<endl;
    ef2d.masseP1_elem(P1_2D, M2);
    ef2d.rigidP1_elem(P1_2D, K2);
    cout<<"Matrice de masse élémentaire pour un triangle : ";
    cout<<M2<<endl;
    cout<<"Matrice de rigidité élémentaire pour un triangle : ";
    cout<<K2<<endl;
    cout<<"\n";


    return 0;
}