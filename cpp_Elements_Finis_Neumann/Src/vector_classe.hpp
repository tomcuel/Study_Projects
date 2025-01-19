//==========================================================================
// classe définissant les vecteurs (de type T, complexe)
//==========================================================================
#ifndef __VECTOR_CLASSE_HPP__
#define __VECTOR_CLASSE_HPP__


#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <utility>
using namespace std;
typedef complex<double> complexe;



//==========================================================================
// utilitaires
//==========================================================================
// message d'arrêt
inline void stop(const string& msg)
{
    cout<<"ERREUR classe Vector, "<<msg;  
    exit(-1); 
}
// test de compatibilité de dimensions de deux vecteurs
inline void test_dim(int d1, int d2, const string& org) 
{
  if (d1==d2) {
    return;
  }
  cout<<org<<" ("<<d1<<","<<d2<<") this->size()s incompatibles";
  exit(-1);
}



//==========================================================================
// classe Vector<T> héritée de vector<T>
//==========================================================================
// définition de la classe
template<typename T>
class Vector : public vector<T>
{
public:
  // constructeurs
  Vector(int d=0, const T& v0=T()); // dim et composantes constantes
  Vector(const initializer_list<T>& vs); // depuis une liste explicite
  template <typename S> Vector(const Vector<S>& vs); // vecteur réel en vecteur complexe
  
  // opérateurs d'accès (par décalage d'indices) : T(i)= valeurs[i-1]
  T  operator ()(int i) const; // en lecture
  T& operator ()(int i); // en écriture
  
  Vector<T>& operator +=(const Vector<T>& v); // u += v
  Vector<T>& operator -=(const Vector<T>& v); // u -= v
  Vector<T>& operator +=(const T& x); // u += x (ajout de x à chaque composante)
  Vector<T>& operator -=(const T& x); // u -= x (soustraction de x à chaque composante)
  Vector<T>& operator *=(const T& x); // u *= x
  Vector<T>& operator /=(const T& x); // u /= x
};


// fonctions membres
//==========================================================================
// constructeur par défaut
template <typename T>
Vector<T>::Vector(int d, const T& v0) : vector<T>(d, v0)
{

}
// constructeur par copie depuis une liste explicite
template <typename T>
Vector<T>::Vector(const initializer_list<T>& vs) : vector<T>(vs)
{

}
// constructeur par copie depuis un vecteur de type différent : vecteur réel en vecteur complexe
template <typename T> template <typename S>
Vector<T>::Vector(const Vector<S>& vs)
{
  this->assign(vs.begin(), vs.end());
}
// opérateurs d'accès (par décalage d'indices) : T(i)= valeurs[i-1]
// valeur T(i) en lecture
template <typename T>
T Vector<T>::operator ()(int i) const
{
  return this->at(i-1);
} 
// valeur T(i) en écriture
template <typename T>
T& Vector<T>::operator ()(int i) 
{ 
  return this->at(i-1);
}       
// u += v
template <typename T>
Vector<T>& Vector<T>::operator +=(const Vector<T>& v)
{
  test_dim(this->size(), v.size(), "op +=");
  for (int i = 0; i < this->size(); i++){
      this->at(i) += v.at(i);
  }
  return *this;
}
// u -= v
template <typename T>
Vector<T>& Vector<T>::operator -=(const Vector<T>& v)
{
  test_dim(this->size(), v.size(), "op -=");
  for (int i = 0; i < this->size(); i++){
    this->at(i) -= v.at(i);
  }
  return *this;
}
// u += x (ajout de x à chaque composante)
template <typename T>
Vector<T>& Vector<T>::operator +=(const T& x)
{
  for (auto& val : *this){
    val += x;
  }
  return *this;
}
// u -= x (soustraction de x à chaque composante)
template <typename T>
Vector<T>& Vector<T>::operator -=(const T& x)
{
  for (auto& val : *this){
    val -= x;
  }
  return *this;
}
// u *= x
template <typename T>
Vector<T>& Vector<T>::operator *=(const T& x)
{
  for (auto& val : *this){
    val *= x;
  }
  return *this;
}
// u /= x
template <typename T>
Vector<T>& Vector<T>::operator /=(const T& x)
{
  if (x == T()){
      stop("op /= : division par 0");
  }
  for (auto& val : *this){
    val /= x;
  }
  return *this;
}


// fonctions externes
//==========================================================================
// <<
template <typename T>
ostream & operator <<(ostream & out, const Vector<T>& u)
{
  if (u.size() <= 0){
      out<<"()";
      return out;
  }
  out<< "(";
  for (int i = 1; i <= u.size()-1; i++){
      out<< u(i)<<", ";
  }
  out<<u(u.size())<<")";
  return out;
}
// +u
template <typename T>
Vector<T> operator +(const Vector<T>& u)
{
  Vector<T> w = u;
  return u;
}
// -u
template <typename T>
Vector<T> operator -(const Vector<T>& u)
{
  Vector<T> w = u;
  return w *= -1;
}
// u + v
template <typename T>
Vector<T> operator +(const Vector<T>& u, const Vector<T>& v)
{
  Vector<T> w = u;
  return w += v;
}
// u - v
template <typename T>
Vector<T> operator -(const Vector<T>& u, const Vector<T>& v)
{
  Vector<T> w = u;
  return w -= v;
}
// u + x (ajout de x à chaque composante)
template <typename T>
Vector<T> operator +(const Vector<T>& u, const T& x)
{
  Vector<T> w = u;
  return w += x;
}
// u - x (soustraction de x à chaque composante)
template <typename T>
Vector<T> operator -(const Vector<T>& u, const T& x)
{
  Vector<T> w = u;
  return w -= x;
}
// x + u (ajout de x à chaque composante)
template <typename T>
Vector<T> operator +(const T& x, const Vector<T>& u)
{
  Vector<T> w = u;
  return w += x;
}
// x - u (ajout de x à chaque composante de -u)
template <typename T>
Vector<T> operator -(const T& x, const Vector<T>& u)
{
  Vector<T> w = -u;
  return w += x;
}
// u * x
template <typename T>
Vector<T> operator *(const Vector<T>& u, const T& x)
{
  Vector<T> w = u;
  return w *= x;
}
// x * u
template <typename T>
Vector<T> operator *(const T& x, const Vector<T>& u)
{
  Vector<T> w = u;
  return w *= x;
}
// u / x
template <typename T>
Vector<T> operator /(const Vector<T>& u, const T& x)
{
  Vector<T> w = u;
  return w /= x;
}
// u == v
template <typename T>
bool operator ==(const Vector<T>& u, const Vector<T>& v)
{
  if (u.size() != v.size()){
      return false;
  }
  for (int i = 1; i <= u.size(); i++){
      if (u(i) != v(i)) {
          return false;
      }
  }
  return true;
}
// u != v
template <typename T>
bool operator !=(const Vector<T>& u, const Vector<T>& v)
{
  return !(u == v);
}
// u | v
template <typename T>
T operator |(const Vector<T>& u, const Vector<T>& v)
{
  test_dim(u.size(), v.size(), "op |");
  T s = 0;
  for (int i = 1; i <= u.size(); i++){
      s += u(i) * v(i);
  }
  return s;
}
// norme
template <typename T>
T norme(const Vector<T>& u)
{
  return sqrt((u | u));
}
// produit hermitien 
template <typename T>
complex<T> operator |(const Vector<complex<T>>& u, const Vector<complex<T>>& v)
{
  test_dim(u.size(), v.size(), "op *");
  complex<T> w = 0;
  for (int i = 1; i <= u.size(); i++){
      w += u(i) * conj(v(i));
  }
  return w;
}
// norme d'un complexe
template <class T>
T norme(const Vector<complex<T>>& u)
{
  return sqrt((u | u).real());
}
// u * x pour u un vecteur de Vector<T>
template <typename T>
Vector<Vector<T>> operator *(const Vector<Vector<T>>& u, const T& x)
{
  Vector<Vector<T>> w = u;
  for (auto& val : w){
    val *= x;
  }
  return w;
}
// x * u pour u un vecteur de Vector<T>
template <typename T>
Vector<Vector<T>> operator *(const T& x, const Vector<Vector<T>>& u)
{
  Vector<Vector<T>> w = u;
  for (auto& val : w){
    val *= x;
  }
  return w;
}
// u / x pour u un vecteur de Vector<T>
template <typename T>
Vector<Vector<T>> operator /(const Vector<Vector<T>>& u, const T& x)
{
  if (x == T()){
      stop("op /= : division par 0");
  }
  Vector<Vector<T>> w = u;
  for (auto& val : w){
    val /= x;
  }
  return w;
}



#endif // __VECTOR_CLASSE_HPP__