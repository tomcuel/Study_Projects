#include "../Src/maillage_classe.hpp"


int main()
{

    // Test 1D = segment [0,1] avec la classe Maillage que l'on remplie manuellement
    Maillage m1(1, "segment [0,1]");
    // Ajout des noeuds
    for (int i = 0; i <= 10; ++i) {
        double x = i * 0.1;
        m1.noeuds.push_back(Point(x));
    }
    // Ajout des éléments (segments connectant les noeuds)
    for (int i = 0; i < 10; ++i) {
        m1.numelts.push_back({i, i + 1});
    }
    m1.print();
    cout<<m1<<endl;
    cout<<"\n";


    // Test 1D = segment [0,2] avec la classe Maillage1D qui remplie automatiquement
    Maillage1D m2(0, 2, 10);
    cout<<m2<<endl;
    cout<<"\n";


    // Test 2D
    Maillage2D m3(2, 5);
    cout<<m3<<endl;
    cout<<"\n";


    // Test Importation d'un maillage 1D à partir d'un fichier
    Maillage m4("../Data/maillage1D.in");
    m4.geometrie = "import 1D";
    cout<<m4<<endl;


    // Test Importation d'un maillage 2D à partir d'un fichier
    Maillage m5("../Data/maillage2D.in");
    m5.geometrie = "import 2D";
    cout<<m5<<endl;


    return 0;
}