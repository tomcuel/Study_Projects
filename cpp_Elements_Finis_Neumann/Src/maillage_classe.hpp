//==========================================================================
// classe définissant le maillages (1D ou 2D)
//==========================================================================
#ifndef __MAILLAGE_CLASSE_HPP__
#define __MAILLAGE_CLASSE_HPP__


#include "point_classe.hpp"
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>



//==========================================================================
// classe Maillage
//==========================================================================
class Maillage
{
public : 
    int dim; // dimension de la géométrie (1 ou 2)
    string geometrie; // nom de la géométrie maillée
    vector<Point> noeuds; // liste des noeuds comptés une seule fois 
    vector<vector<int>> numelts; // liste des éléments (segments ou triangles)

    Maillage(int d=0, const string& geo = ""); // constructeur
    Maillage(const string& nom_fichier); // constructeur à partir d'un fichier représentant le maillage

    void print(ostream & out=cout) const; // affichage du maillage 

    void exporte(const string& nom_fichier) const; // exporte les données du maillage dans un fichier

};


// fonctions membres de la classe Maillage
//==========================================================================
// constructeur
Maillage::Maillage(int d,const string& geo) : dim(d), geometrie(geo)
{

}
// constructeur à partir d'un fichier représentant le maillage
Maillage::Maillage(const string& nom_fichier)
{
    ifstream fichier(nom_fichier);
    if (!fichier){
        cerr<<"Erreur: impossible d'ouvrir le fichier "<<nom_fichier<<endl;
        exit(-1);
    }
    // dimensions du maillage
    string line;
    getline(fichier, line);
    dim = stoi(line);

    // importation des noeuds
    getline(fichier, line);
    int nb_noeuds = stoi(line);
    getline(fichier, line);
    for (int i = 0; i < nb_noeuds; ++i){
        int pos = line.find(";");
        string node = line.substr(0, pos);
        line.erase(0, pos + 1);
        if (dim == 1){
            double x = stod(node.substr(1, node.size() - 2));
            noeuds.push_back(Point(x));
        }
        else if (dim == 2){
            pos = node.find(",");
            double x = stod(node.substr(1, pos));
            double y = stod(node.substr(pos + 1, node.size() - 2));
            noeuds.push_back(Point(x, y));
        }
    }

    // importation des éléments
    getline(fichier, line);
    int nb_elements = stoi(line);
    getline(fichier, line);
    for (int i = 0; i < nb_elements; ++i){
        int pos = line.find(";");
        string element = line.substr(0, pos);
        line.erase(0, pos + 1);
        vector<int> elt;
        if (dim == 1){
            pos = element.find(",");
            int p1 = stoi(element.substr(1, pos));
            int p2 = stoi(element.substr(pos + 1, element.size() - 2));
            elt.push_back(p1);
            elt.push_back(p2);
        }
        else if (dim == 2){
            int pos1 = element.find(",");
            int pos2 = element.find(",", pos1 + 1);
            int p1 = stoi(element.substr(1, pos1));
            int p2 = stoi(element.substr(pos1 + 1, pos2));
            int p3 = stoi(element.substr(pos2 + 1, element.size() - 2));
            elt.push_back(p1);
            elt.push_back(p2);
            elt.push_back(p3);
        }
        numelts.push_back(elt);
    }

    fichier.close();
    // pas besoin d'exporter vu qu'on a importé le maillage d'un fichier contenant les mêmes données
}
// print
void Maillage::print(ostream& out) const
{
    out<<"Maillage de "<<geometrie<<"\n";

    // Affichage des noeuds
    out<<"Liste des noeuds ("<<noeuds.size()<<" points)\n";
    for (int i = 0; i < noeuds.size(); ++i){
        out<<noeuds[i];
        if (i != noeuds.size()-1){
            out<<",";
        }
    }
    out<<"\n";

    // Affichage des éléments
    out<<"Liste des éléments ("<<numelts.size()<<" segments)\n";
    for (int i = 0; i < numelts.size(); ++i){
        out<<"(";
        for (int j = 0; j < numelts[i].size(); ++j){
            out<<numelts[i][j];
            if (j != numelts[i].size()-1){
                out<<",";
            }
        }
        out<<")";
        if (i != numelts.size()-1){
            out<<",";
        }
    }
    out<<"\n";
}
// exporte les données du maillage dans un fichier in
void Maillage::exporte(const string& nom_fichier) const
{
    ofstream fichier(nom_fichier);
    if (!fichier){
        cerr<<"Erreur: impossible de créer le fichier "<<nom_fichier<<endl;
        exit(-1);
    }
    // dimensions du maillage
    fichier<<dim<<"\n";

    // Exportation des noeuds
    fichier<<noeuds.size()<<"\n";
    for (int i = 0; i < noeuds.size(); ++i){
        fichier<<noeuds[i];
        if (i != noeuds.size()-1){
            fichier<<";";
        }
    }
    fichier<<"\n";

    // Exportation des éléments
    fichier<<numelts.size()<<"\n";
    for (int i = 0; i < numelts.size(); ++i){
        fichier<<"(";
        for (int j = 0; j < numelts[i].size(); ++j){
            fichier<<numelts[i][j];
            if (j != numelts[i].size()-1){
                fichier<<",";
            }
        }
        fichier<<")";
        if (i != numelts.size()-1){
            fichier<<";";
        }
    }
    fichier<<"\n";
    fichier.close();
}


// fonctions externes
//==========================================================================
//<<
ostream& operator<<(ostream& out, const Maillage& M)
{
    out<<"Maillage "<<M.geometrie<<"\n";

    // Affichage des noeuds
    out<<"Liste des noeuds ("<<M.noeuds.size()<<" points)\n";
    for (int i = 0; i < M.noeuds.size(); ++i){
        out<<M.noeuds[i];
        if (i != M.noeuds.size()-1){
            out<<",";
        }
    }
    out<<"\n";

    // Affichage des éléments
    out<<"Liste des éléments ("<<M.numelts.size()<<" segments)\n";
    for (int i = 0; i < M.numelts.size(); ++i){
        out<<"(";
        for (int j = 0; j < M.numelts[i].size(); ++j){
            out<<M.numelts[i][j];
            if (j != M.numelts[i].size()-1){
                out<<",";
            }
        }
        out<<")";
        if (i != M.numelts.size() - 1){
            out<<",";
        }
    }
    out<<"\n";
    return out;
}



//==========================================================================
// classe Maillage1D
//==========================================================================
class Maillage1D : public Maillage
{
public : 
    Maillage1D(double a, double b, int m); // constructeur du maillage du segment [a,b] en m intervalles
};


// fonctions membres
//==========================================================================
// constructeur du maillage 1D du segment [a,b] en m intervalles
Maillage1D::Maillage1D(double a, double b, int m) : Maillage(1, "1D du segment ["+to_string(a)+","+to_string(b)+"] en "+to_string(m)+" intervalles")
{
    dim = 1;
    geometrie = "Maillage1D du segment ["+to_string(a)+","+to_string(b)+"] en "+to_string(m)+" intervalles";
    for (int i = 0; i <= m; ++i){
        double x = a + i * (b - a) / m;
        noeuds.push_back(Point(x));
    }
    for (int i = 0; i < m; ++i){
        numelts.push_back({i, i + 1});
    }
    exporte("../Data/maillage1D.in"); // exporte les données du maillage dans un fichier
}



//==========================================================================
// classe Maillage2D
//==========================================================================
class Maillage2D : public Maillage
{
public : 
    Maillage2D(int m, int n); // constructeur du maillage du carré unité [0,1]x[0,1] en m x n mailles
    Maillage2D(double a, double b, int m, int n); // constructeur du maillage du carré [a,b]x[a,b] en m x n mailles
    Maillage2D(double a, double b, double c, double d, int m, int n); // constructeur du maillage du carré [a,b]x[c,d] en m x n mailles
    void maille_carre_unite(int m, int n); // méthode pour le maillage du carré unité
};


// fonctions membres
//==========================================================================
// constructeur du maillage du carré unité [0,1]x[0,1] en m x n mailles
Maillage2D::Maillage2D(int m, int n) : Maillage(2, "carré unité [0,1]x[0,1] en "+to_string(m)+ "x"+to_string(n)+" mailles")
{
    maille_carre_unite(m, n);
    exporte("../Data/maillage2D.in"); // exporte les données du maillage dans un fichier
}
// constructeur du maillage du carré [a,b]x[a,b] en m x n mailles
Maillage2D::Maillage2D(double a, double b, int m, int n) : Maillage(2, "rectangle ["+to_string(a)+","+to_string(b)+"]x["+to_string(a)+","+to_string(b)+"]") 
{
    maille_carre_unite(m, n); // on crée le carré unité que l'on va dilater
    // Transformation affine des noeuds
    for (auto& node : noeuds){
        node.x = node.x * a;
        node.y = node.y * b;
    }
    exporte("../Data/maillage2D.in"); // exporte les données du maillage dans un fichier
}
// constructeur du maillage du carré [a,b]x[c,d] en m x n mailles
Maillage2D::Maillage2D(double a, double b, double c, double d, int m, int n) : Maillage(2, "rectangle ["+to_string(a)+","+to_string(b)+"]x["+to_string(c)+","+to_string(d)+"]") 
{
    maille_carre_unite(m, n); // on crée le carré unité que l'on va dilater
    // Transformation affine des noeuds
    for (auto& node : noeuds){
        node.x = a + node.x * (b - a);
        node.y = c + node.y * (d - c);
    }
    exporte("../Data/maillage2D.in"); // exporte les données du maillage dans un fichier
}

// méthode pour la création du maillage du carré unité
void Maillage2D::maille_carre_unite(int m, int n){
    noeuds.clear();
    numelts.clear();

    // Création des noeuds du maillage carré unité
    for (int j = 0; j <= n; ++j){
        for (int i = 0; i <= m; ++i){
            noeuds.push_back(Point(i/(double)m, j/(double)n));
        }
    }

    srand(time(nullptr)); // initialisation du générateur de nombres aléatoires pour diviser les rectangles en 2 triangles de manière aléatoire
    for (int j = 0; j < n; ++j){ // 1 rectangle de moins que de noeuds
        for (int i = 0; i < m; ++i){ // 1 rectangle de moins que de noeuds

            // indice des points du carré dans la liste (i,j) --> i + j*(m+1)
            int p1_idx = i + j *(m + 1); // (i,j)
            int p2_idx = i+1 + j *(m + 1); // (i+1,j)
            int p3_idx = i + (j+1) *(m + 1); // (i,j+1)
            int p4_idx = i+1 + (j+1) *(m + 1); // (i+1,j+1)

            // On séparer en 2 triangles de manière aléatoire selon le résult de rand()
            if (rand() % 2 == 0){
                numelts.push_back({p1_idx, p2_idx, p3_idx}); // triangle 1
                numelts.push_back({p2_idx, p4_idx, p3_idx}); // triangle 2
            }
            else{
                numelts.push_back({p1_idx, p2_idx, p4_idx}); // triangle 1
                numelts.push_back({p1_idx, p4_idx, p3_idx}); // triangle 2
            }
        }
    }
}



#endif // __MAILLAGE_CLASSE_HPP__