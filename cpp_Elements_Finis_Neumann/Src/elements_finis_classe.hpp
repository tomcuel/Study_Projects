//==========================================================================
// classe définissant les éléments finis (1D ou 2D) de type double
//==========================================================================
#ifndef __ELEMENTS_FINIS_CLASSE_HPP__
#define __ELEMENTS_FINIS_CLASSE_HPP__


#include "point_classe.hpp"
#include "sparse_classe.hpp"
typedef Vector<Point> Vecteur_Points;
typedef Sparse<double> Matrice;



//==========================================================================
//classe EF (éléments finis)
//==========================================================================
class EF
{
public : 
    int dim; // dimension de l'élément (1 ou 2)
    EF(int d); // constructeur
    virtual void masseP1_elem(const Vecteur_Points& P, Matrice& M) const=0; // matrice de masse élémentaire
    virtual void rigidP1_elem(const Vecteur_Points& P, Matrice& K)const=0; // matrice de rigidité élémentaire
};


// fonctions membres
//==========================================================================
// constructeur
EF::EF(int d) : dim(d) 
{

}



//==========================================================================
//classe EF1D (pour les segments)
//==========================================================================
class EF1D : public EF 
{
public:
    EF1D(); // constructeur

    void masseP1_elem(const Vecteur_Points& P, Matrice& M) const override; // matrice de masse élémentaire
    void rigidP1_elem(const Vecteur_Points& P, Matrice& K) const override; // matrice de rigidité élémentaire
};


// fonctions membres
//==========================================================================
// constructeur
EF1D::EF1D() : EF(1) 
{

}
// Calcul de la matrice de masse élémentaire pour un segment
void EF1D::masseP1_elem(const Vecteur_Points& P, Matrice& M) const
{
    // P contient les coordonnées des 2 noeuds du segment
    if (P.size() != 2){
        cout << "erreur : segment mal défini" << endl;
        exit(-1);
    }
    // M matrice 2x2 normalement 
    M.m = 2;
    M.n = 2;
    double coef = abs(P[1].x - P[0].x) / 6.;
    // Calcul de la matrice de masse
    M(1, 1) = 2 * coef;
    M(1, 2) = coef;
    M(2, 1) = coef;
    M(2, 2) = 2 * coef;
}
// Calcul de la matrice de rigidité élémentaire pour un segment
void EF1D::rigidP1_elem(const Vecteur_Points& P, Matrice& K) const
{
    // P contient les coordonnées des 2 noeuds du segment
    if (P.size() != 2){
        cout << "erreur : segment mal défini" << endl;
        exit(-1);
    }
    // M matrice 2x2 normalement 
    K.m = 2;
    K.n = 2;
    double abs_s12 = abs(P[1].x - P[0].x);
    if (abs_s12 == 0.0){
        cout << "erreur : segment de longueur nulle" << endl;
        exit(-1);
    }
    // Calcul de la matrice de rigidité
    K(1, 1) = 1 / abs_s12;
    K(1, 2) = -1 / abs_s12;
    K(2, 1) = -1 / abs_s12;
    K(2, 2) = 1 / abs_s12;
}



//==========================================================================
//classe EF2D (pour les triangles)
//==========================================================================
class EF2D : public EF 
{
public:
    EF2D(); // constructeur

    void masseP1_elem(const Vecteur_Points& P, Matrice& M) const override; // matrice de masse élémentaire
    void rigidP1_elem(const Vecteur_Points& P, Matrice& K) const override; // matrice de rigidité élémentaire
};


// fonctions membres
//==========================================================================
// constructeur
EF2D::EF2D() : EF(2) 
{
    
}
// Calcul de la matrice de masse élémentaire pour un triangle
void EF2D::masseP1_elem(const Vecteur_Points& P, Matrice& M) const
{
    // P contient les coordonnées des 3 noeuds du triangle
    if (P.size() != 3){
        cout << "erreur : triangle mal défini" << endl;
        exit(-1);
    }
    // M matrice 3x3 normalement
    M.m = 3;
    M.n = 3;
    double m = mesure(P[0],P[1],P[2]);
    // Calcul de la matrice de masse
    for (int i = 1; i <= 3; ++i){
        for (int j = 1; j <= 3; ++j){
            if (i == j){
                M(i, j) = m / 6.;
            }
            else{
                M(i, j) = m / 12.;
            }
        }
    }
}
// Calcul de la matrice de rigidité élémentaire pour un triangle
void EF2D::rigidP1_elem(const Vecteur_Points& P, Matrice& K) const
{
    // P contient les coordonnées des 3 noeuds du triangle
    if (P.size() != 3){
        cout << "erreur : triangle mal défini" << endl;
        exit(-1);
    }
    // K matrice 3x3 normalement
    K.m = 3;
    K.n = 3;
    double m = mesure(P[0],P[1],P[2]);
    if (m == 0.0){
        cout << "erreur : triangle de surface nulle" << endl;
        exit(-1);
    }
    double coeff = 1 / (4 * m);
    Point s12 = P[1] - P[0];
    Point s23 = P[2] - P[1];
    Point s13 = P[2] - P[0];
    // Calcul de la matrice de rigidité
    K(1, 1) = coeff * (s23 | s23);
    K(2, 2) = coeff * (s13 | s13);
    K(3, 3) = coeff * (s12 | s12);
    K(1, 2) = K(2, 1) = - coeff * (s23 | s13);
    K(1, 3) = K(3, 1) = - coeff * (s23 | s12);
    K(2, 3) = K(3, 2) = - coeff * (s13 | s12);
}



#endif // __ELEMENTS_FINIS_CLASSE_HPP__