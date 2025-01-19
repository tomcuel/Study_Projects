//==========================================================================
// classe définissant la résolution d'une équation de Neumann
//==========================================================================
#ifndef __NEUMANN_CLASSE_HPP__
#define __NEUMANN_CLASSE_HPP__


#include "maillage_classe.hpp"
#include "elements_finis_classe.hpp"
typedef double(*fun)(const Point& P); // pointeur de fonction R2->R
typedef Vector<double> Vecteur;



//====================================
// classe Neumann
//====================================
// MT un type de maillage (Maillage1D ou Maillage2D) et EFT un type d'élément fini (EF1D ou EF2D)
template <typename MT, typename EFT>
class Neumann
{
public :
    MT maille; // pointeur sur un maillage de type MT
    EFT ef; // élément fini de type EFT
    double k; // nombre d'onde du problème
    int nb_iter; // nombre d'itérations pour la résolution du système
    fun f, uex; // fonction f et uex (u_exacte)
    Matrice M,K; // matrices de masse et de rigidité
    Vecteur sol; // vecteur solution
    Neumann(const MT& m, double k, fun f, fun uex = nullptr); // constructeur
    void assembleMatrices(); // assemblage des matrices K et M à partir des matrices élémentaires
    void resoudre(); // résolution du système (K+k^2M)*U=M*F
    void calculErreur_L2(); // calcul de l'erreur ||U-Uex||_L2
    void exporte(const string& nom_fichier) const; // exporte les résultats dans un fichier in
};

// fonctions membres
//====================================
// constructeur
template <typename MT, typename EFT>
Neumann<MT, EFT>::Neumann(const MT& m, double k, fun f, fun uex) : maille(m), k(k), nb_iter(0), f(f), uex(uex), M(m.noeuds.size(), m.noeuds.size()), K(m.noeuds.size(), m.noeuds.size())
{

}
// assemblage des matrices K et M
template <typename MT, typename EFT>
void Neumann<MT, EFT>::assembleMatrices()
{
    // boucle sur tous les éléments du maillage (triangles ou segments)
    for (const auto& element : maille.numelts){
        // Récupération des coordonnées des noeuds de l'élément
        Vecteur_Points Points_local;
        for (int i = 0; i < element.size(); ++i){
            Points_local.push_back(maille.noeuds[element[i]]);
        }

        // Calcul des matrices élémentaires
        Matrice Me(Points_local.size(), Points_local.size());
        Matrice Ke(Points_local.size(), Points_local.size());
        ef.masseP1_elem(Points_local, Me);
        ef.rigidP1_elem(Points_local, Ke);

        // Assemblage des matrices élémentaires dans les matrices globales (la taille sera ajustée automatiquement par les opérateurs de Sparse)
        for (int i = 0; i < element.size(); ++i){
            for (int j = 0; j < element.size(); ++j){
                M(element[i]+1, element[j]+1) += Me(i+1, j+1);
                K(element[i]+1, element[j]+1) += Ke(i+1, j+1);
            }
        }
        
    }
}
// résolution du système (K+k^2M)*U=M*F
template <typename MT, typename EFT>
void Neumann<MT, EFT>::resoudre()
{
    // Construction de K+k^2*M
    Matrice A = K + ((k*k)*M);

    // Construction de F 
    Vecteur F(maille.noeuds.size(), 0.0);
    for (int i = 0; i < maille.noeuds.size(); ++i){
        F[i] = f(maille.noeuds[i]);
    }
    Vecteur b = M * F; // M*F

    // Solution initiale comme vecteur nul au début
    Vecteur U0(maille.noeuds.size(), 0.0);

    // Solve the system using the conjugate gradient method
    sol = gradConj(A, b, U0, 1000, 1e-8, &nb_iter);
}
// calcul de l'erreur ||U-Uex||_L2 = sqrt( sum_i (U_i - Uex_i)^2 )
template <typename MT, typename EFT>
void Neumann<MT, EFT>::calculErreur_L2()
{
    if (!uex){
        cerr<<"On n'a pas de solution exacte pour calculer l'erreur"<<endl;
        exit(-1);
    }

    // Calcul de l'erreur L2
    Vecteur diff = sol;
    for (int i = 0; i < maille.noeuds.size(); ++i){
        diff[i] -= uex(maille.noeuds[i]);
    }
    double error = (M * diff | diff);
    error = sqrt(error);

    // ajout de l'erreur à la fin du fichier de sortie
    string output_file;
    if (maille.dim == 1){
        output_file = "../Data/solution1D.in";
    } else if (maille.dim == 2){
        output_file = "../Data/solution2D.in";
    } 
    else {
        cerr<<"Dimension non supportée pour l'écriture de l'erreur"<<endl;
        exit(-1);
    }

    ofstream file(output_file, ios::app);
    if (!file){
        cerr<<"Impossible d'ouvrir le fichier de sortie "<<output_file<<endl;
        exit(-1);
    }

    file<<error<<endl;
    file.close();
    
}
// exporte les résultats dans un fichier in 
template <typename MT, typename EFT>
void Neumann<MT, EFT>::exporte(const string& nom_fichier) const
{
    ofstream fichier(nom_fichier);
    if (!fichier.is_open()){
        cerr<<"Erreur : impossible d'ouvrir le fichier "<<nom_fichier<<endl;
        return;
    }
    if (maille.dim == 1){
        // En 1D, on exporte les coordonnées des sommets et la solution en ces points
        fichier<<"1\n"<<endl;
        for (int i = 0; i < sol.size(); ++i){
            fichier<<maille.noeuds[i].x<<" "<<sol[i]<<endl;
        }
    }
    else if (maille.dim == 2){
        // En 2D, on exporte les coordonnées des sommets et la solution en ces points et la numérotation des éléments
        fichier<<"2\n"<<endl;
        for (int i = 0; i < sol.size(); ++i){
            fichier<<maille.noeuds[i].x<<" "<<maille.noeuds[i].y<<" "<<sol[i]<<endl;
        }
        fichier<<"\n";
        for (int i = 0; i < maille.numelts.size(); ++i){
            for (int j = 0; j < maille.numelts[i].size(); ++j){
                fichier<<maille.numelts[i][j]<<" ";
            }
            fichier<<endl;
        }
    }
    fichier<<"\n";
    fichier<<nb_iter<<endl;
    fichier<<"\n";
}



#endif // __NEUMANN_CLASSE_HPP__