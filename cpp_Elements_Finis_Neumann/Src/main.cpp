#include "neumann_classe.hpp"


// Fonction f associée pour tester la solution exacte uex du problème de Neumann 1D
double fonction_uex_1D(const Point& P) {
    return ((1-cos(1))/sin(1))*cos(P.x) - sin(P.x) + P.x;
}
double fonction_f_1D(const Point& P) {
    return P.x;
}
// Fonction f associée pour tester la solution exacte uex du problème de Neumann 2D
double fonction_uex_2D(const Point& P) {
    return 3 * cos (M_PI * P.x) * cos (2 * M_PI * P.y);
}
double fonction_f_2D(const Point& P) {
    return (3 + 15 * M_PI * M_PI) * cos(M_PI * P.x) * cos (2 * M_PI * P.y);
}


int main()
{
    // Test de la classe Neumann 1D
    // Création d'un maillage 1D du segment [0,1] divisé en 4 intervalles
    Maillage1D mesh1D(0, 1, 4);
    // Création de l'objet Neumann
    Neumann<Maillage1D, EF1D> neumann_solver_1D(mesh1D, 1, fonction_f_1D, fonction_uex_1D);
    // Assemblage des matrices de masse et de rigidité
    neumann_solver_1D.assembleMatrices();
    // Résolution du système linéaire
    neumann_solver_1D.resoudre();
    // exporter la solution dans un fichier 
    neumann_solver_1D.exporte("../Data/solution1D.in");
    // ajouter l'erreur L2 dans le fichier de sortie
    neumann_solver_1D.calculErreur_L2();
    

    // Test de la classe Neumann 2D
    // Création d'un maillage 2D du [0,2]x[0,2] divisé en 10x10 mailles
    Maillage2D mesh2D(2.0, 2.0, 10, 10);
    // Création de l'objet Neumann
    Neumann<Maillage2D, EF2D> neumann_solver_2D(mesh2D, 1, fonction_f_2D, fonction_uex_2D);
    // Assemblage des matrices de masse et de rigidité
    neumann_solver_2D.assembleMatrices();
    // Résolution du système linéaire
    neumann_solver_2D.resoudre();
    // exporter la solution dans un fichier 
    neumann_solver_2D.exporte("../Data/solution2D.in");
    // ajouter l'erreur L2 dans le fichier de sortie
    neumann_solver_2D.calculErreur_L2();


    return 0;
}