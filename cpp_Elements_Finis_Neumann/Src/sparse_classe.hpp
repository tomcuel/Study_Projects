//==========================================================================
// classe définissant les matrices creuses Sparse de type T
//==========================================================================
#ifndef __SPARSE_CLASSE_HPP__
#define __SPARSE_CLASSE_HPP__


#include "vector_classe.hpp"
// les autres includes sont dans Vecteur.hpp
#include <map>
#include <cmath>



//==========================================================================
// classe Pint (pair<int,int>)
//==========================================================================
typedef pair<int, int> Pint;
// surcharge de < pour les Pint
inline bool operator <(const Pint &ij1, const Pint &ij2)
{
    return (ij1.first < ij2.first || (ij1.first == ij2.first && ij1.second < ij2.second));
}
// affichage d'une paire d'entiers
inline ostream &operator <<(ostream &os, const Pint &ij)
{
    os<<"("<<ij.first<<","<<ij.second<<")";
    return os;
}



//==========================================================================
// classe Sparse<T> héritée de map<Pint,T>
//==========================================================================
template <typename T>
class Sparse : public map<Pint, T>
{
public:
    int m, n; // dimensions de la matrice

    Sparse(int mi = 0, int ni = 0); // constructeur

    // accès à l'élément (i,j) : indices de 1 à m et de 1 à n
    T operator ()(int i, int j) const; // en lecture
    T &operator ()(int i, int j); // en écriture

    void supprime(int i, int j); // supprime l'élément (i,j) si présent de la map

    Sparse<T> &operator +=(const Sparse<T> &M); // S+=M
    Sparse<T> &operator -=(const Sparse<T> &M); // S-=M
    Sparse<T> &operator +=(const T &s); // S+=s (ajout de s à chaque élément)
    Sparse<T> &operator -=(const T &s); // S-=s (soustraction de s à chaque élément)
    Sparse<T> &operator *=(const T &s); // *=s
    Sparse<T> &operator /=(const T &s); // /=s

    void remplissage() const; // affiche le remplissage de la matrice
};


// fonctions membres
//==========================================================================
// constructeur
template <typename T>
Sparse<T>::Sparse(int mi, int ni) : m(mi), n(ni)
{
    
}
// accès à l'élément (i,j) en lecture
template <typename T>
T Sparse<T>::operator ()(int i, int j) const
{
    if (i < 1 || i > m || j < 1 || j > n) {
        cout<<"erreur : indices hors limites"<<endl;
        exit(-1);
    }
    auto it = this->find(Pint(i, j));
    if (it == this->end())
    {
        return T();
    }
    return it->second;
}
// accès à l'élément (i,j) en écriture
template <typename T>
T &Sparse<T>::operator ()(int i, int j)
{   
    if (i < 1 || j < 1) {
        cout<<"erreur : indices hors limites"<<endl;
        exit(-1);
    }
    Pint ij(i,j);
    auto itm=this->find(ij);
    if(itm == this->end()){
        if(i>m){
            m=i;
        }
        if(j>n){
            n=j;
        }
        return(*this)[ij]=T(); // crée l'élément avec la valeur par défaut à l'indice (i,j)
    }
    return itm->second;
}
// afficher la structure rempli de la matrice
// on numérote les colonnes de 1 à n et les lignes de 1 à m
// en affichant que les chiffres des unités pour ne pas avoir à compter les décalages potentiels à faire
// on met des x pour les éléments non nuls
template <typename T>
void Sparse<T>::remplissage() const
{
    // Afficher la première ligne avec les numéros de colonnes
    cout<<"  "; // espace pour les numéros de ligne
    for (int j = 1; j <= n; ++j)
    {
        cout<<j % 10<<" "; // Affiche seulement le chiffre des unités
    }
    cout<<endl;

    // Afficher les lignes de la matrice
    for (int i = 1; i <= m; ++i)
    {
        cout<<i % 10<<" "; // Affiche seulement le chiffre des unités pour les lignes devant la ligne de la matrice
        for (int j = 1; j <= n; ++j)
        {
            // Afficher un "x" si l'élément est non nul, sinon un espace
            if ((*this)(i,j) != 0.)
            {
                cout<<"x ";
            }
            else
            {
                cout<<"  "; // Deux espaces pour aligner
            }
        }
        cout<<endl;
    }
    cout<<endl;
}
// S+=M
template <typename T>
Sparse<T> &Sparse<T>::operator +=(const Sparse<T> &M)
{
    // additionner les éléments
    for (auto it = M.begin(); it != M.end(); ++it){
        auto key = it->first;
        auto value = it->second;
        if (key.first > m){
            m = key.first;
        }
        if (key.second > n){
            n = key.second;
        }
        auto itm=this->find(key);
        if (itm != this->end()){
            itm->second += value;
            if (itm->second == T()){
                this->erase(itm);
            }
        } 
        else {
            (*this)[key] = value;
        }
    }
    return *this;
}
// S-=M
template <typename T>
Sparse<T> &Sparse<T>::operator -=(const Sparse<T> &M)
{
    for (auto it = M.begin(); it != M.end(); ++it){
        auto key = it->first;
        auto value = it->second;
        if (key.first > m){
            m = key.first;
        }
        if (key.second > n){
            n = key.second;
        }
        auto itm=this->find(key);
        if (itm != this->end()){
            itm->second -= value;
            if (itm->second == T()){
                this->erase(itm);
            }
        } 
        else {
            (*this)[key] = -value;
        }
    }
    return *this;
}
// S+=s
template <typename T>
Sparse<T> &Sparse<T>::operator +=(const T &s)
{
    for (auto it = this->begin(); it != this->end(); ++it){
        it->second += s;
        if (it->second == T()){
            it = this->erase(it); // Erase and advance iterator
        }
    }
    return *this;
}
// S-=s
template <typename T>
Sparse<T> &Sparse<T>::operator -=(const T &s)
{
    for (auto it = this->begin(); it != this->end(); ++it){
        it->second -= s;
        if (it->second == T()){
            it = this->erase(it); // Erase and advance iterator
        }
    }
    return *this;
}
// *=
template <typename T>
Sparse<T> &Sparse<T>::operator *=(const T &s)
{
    for (auto it = this->begin(); it != this->end(); ++it){
        it->second *= s;
    }
    return *this;
}
// /=
template <typename T>
Sparse<T> &Sparse<T>::operator /=(const T &s)
{
    if (s == T()){
        cout<<"op /= : division par 0"<<endl;
        exit(-1);
    }
    for (auto it = this->begin(); it != this->end(); ++it){
        it->second /= s;
    }
    return *this;
}


// fonctions externes
//==========================================================================
// <<
template <typename T>
ostream &operator <<(ostream &os, const Sparse<T> &matrice)
{
    os<<"\nmatrice sparse "<<matrice.m<<"x"<<matrice.n<<", nb coeff="<<matrice.size()<<endl;
    for (auto it = matrice.begin(); it != matrice.end(); ++it){
        os<<it->first<<" : "<<it->second<<endl;
    }
    return os;
}
// +M
template <typename T>
Sparse<T> operator +(const Sparse<T> &M)
{
    Sparse<T> R(M);
    return R;
}
// -M
template <typename T>
Sparse<T> operator -(const Sparse<T> &M)
{
    Sparse<T> R(M);
    R *= -1;
    return R;
}
// M+N
template <typename T>
Sparse<T> operator +(const Sparse<T> &M, const Sparse<T> &N)
{
    Sparse<T> R(M);
    R += N;
    return R;
}
// M-N
template <typename T>
Sparse<T> operator -(const Sparse<T> &M, const Sparse<T> &N)
{
    Sparse<T> R(M);
    R -= N;
    return R;
}
// M+s (ajout de s à chaque élément)
template <typename T>
Sparse<T> operator +(const Sparse<T> &M, const T &s)
{
    Sparse<T> R(M);
    R += s;
    return R;
}
// M-s (soustraction de s à chaque élément)
template <typename T>
Sparse<T> operator -(const Sparse<T> &M, const T &s)
{
    Sparse<T> R(M);
    R -= s;
    return R;
}
// s+M (ajout de s à chaque élément)
template <typename T>
Sparse<T> operator +(const T &s, const Sparse<T> &M)
{
    Sparse<T> R(M);
    R += s;
    return R;
}
// s-M (soustraction de chaque élément à s)
template <typename T>
Sparse<T> operator -(const T &s, const Sparse<T> &M)
{
    Sparse<T> R(M);
    R -= s;
    return R;
}
// s*M
template <typename T>
Sparse<T> operator *(const T &s, const Sparse<T> &M)
{
    Sparse<T> R(M);
    R *= s;
    return R;
}
// M*s
template <typename T>
Sparse<T> operator *(const Sparse<T> &M, const T &s)
{
    Sparse<T> R(M);
    R *= s;
    return R;
}
// M/s
template <typename T>
Sparse<T> operator /(const Sparse<T> &M, const T &s)
{
    Sparse<T> R(M);
    R /= s; // message d'erreur déjà inclus dans l'opérateur /= de Sparse
    return R;
}
// M==N
template <typename T>
bool operator ==(const Sparse<T> &M, const Sparse<T> &N)
{
    if (M.m != N.m || M.n != N.n){
        return false;
    }
    for (auto it = M.begin(); it != M.end(); ++it){
        if (N(it->first.first, it->first.second) != it->second){
            return false;
        }
    }
    return true;
}
// M!=N
template <typename T>
bool operator !=(const Sparse<T> &M, const Sparse<T> &N)
{
    return !(M == N);
}
// M*T (Matrice * Vecteur)
template <typename T>
Vector<T> operator *(const Sparse<T> &M, const Vector<T> &vec)
{
    // vérifier que les dimensions matchent
    if (M.n != vec.size()){
        cout<<"erreur : dimensions incompatibles"<<endl;
        exit(-1);
    }
    Vector<T> result = Vector<T>(M.m, T()); // allouer la mémoire et initialisé le vecteur avec des 0
    for (auto it = M.begin(); it != M.end(); ++it){
        // matrice d'indice de 1 à n et pas de 0 à n-1
        result[it->first.first - 1] += it->second * vec[it->first.second - 1];
    }
    return result;
}
// méthode du gradient conjugué pour résoudre le système linéaire A*x=b
template <typename T>
Vector<T> gradConj(const Sparse<T> &A, const Vector<T> &b, const Vector<T> &x0, int kmax, const T &eps = 1e-4, int* kiter = nullptr) // kiter = nullptr pour un passage par argument optionnel
{
    // initialisation de X0, G0, W0
    Vector<T> X = x0;
    Vector<T> G = (A * x0) - b;
    Vector<T> Gk = G;
    T theta = T();
    Vector<T> W = G;
    for (int k = 0; k < kmax; ++k){
        theta = (G|W) / (A * W|W);
        X = X - (theta * W);
        Gk = G;
        G = G - theta * (A * W);
        // condition d'arrêt
        if (norme(G) < eps * norme(b)){
            if (kiter != nullptr){
                *kiter = k;
            }
            cout<<"convergence en "<<k<<" itérations à la précision "<<eps<<endl;
            return X;
        }
        W = G + (G|G) / (Gk|Gk) * W;
    }
    cout<<"pas de convergence en "<<kmax<<" itérations"<<endl;
    return X;
}



#endif // __SPARSE_CLASSE_HPP__