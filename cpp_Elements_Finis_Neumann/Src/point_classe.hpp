//==========================================================================
// classe définissant les points d'un maillage (1D ou 2D) de type double
//==========================================================================
#ifndef __POINT_CLASSE_HPP__
#define __POINT_CLASSE_HPP__


#include <iostream>
#include <cmath>
#include <utility>
using namespace std;



//==========================================================================
//classe Point
//==========================================================================
class Point 
{
public : 
    int dim; // dimension du point (1 ou 2)
    double x, y; // abscisse et ordonnée
    
    // constructeurs
    Point(); // par défaut
    Point(double a); // 1D
    Point(double a, double b); // 2D

    Point& operator +=(const Point& Q); // P+=Q
    Point& operator -=(const Point& Q); // P-=Q
    Point& operator +=(const double& a); // P+=a (ajout de a à chaque composante)
    Point& operator -=(const double& a); // P-=a (soustraction de a à chaque composante)
    Point& operator *=(const double& a); // P*=a
    Point& operator /=(const double& a); // P/=a
};


// fonctions membres
//==========================================================================
// constructeur par défaut (0D) 
Point::Point() : dim(0), x(0), y(0)
{

}
// constructeur 1D 
Point::Point(double a) : dim(1), x(a), y(0)
{

}
// constructeur 2D 
Point::Point(double a, double b) : dim(2), x(a), y(b)
{

}
// P+=Q 
Point& Point::operator +=(const Point& Q)
{
    if (this->dim == 0 || Q.dim == 0 || this->dim != Q.dim){
        throw invalid_argument("Error: The vector is of dimension 0 or the vectors are of different sizes. Cannot perform addition.");
    }
    if (this->dim == 1){
        this->x += Q.x;
    }
    else if (this->dim == 2){
        this->x += Q.x;
        this->y += Q.y;
    }
    return *this;
}
// P-=Q
Point& Point::operator -=(const Point& Q)
{
    if (this->dim == 0 || Q.dim == 0 || this->dim != Q.dim){
        throw invalid_argument("Error: The vector is of dimension 0 or the vectors are of different sizes. Cannot perform subtraction.");
    }
    if (this->dim == 1){
        this->x -= Q.x;
    }
    else if (this->dim == 2){
        this->x -= Q.x;
        this->y -= Q.y;
    }
    return *this;
}
// P+=a (ajout de a à chaque composante)
Point& Point::operator +=(const double& a)
{
    if (this->dim == 0){
        throw invalid_argument("Error: The vector is of dimension 0. Cannot perform addition.");
    }
    this->x += a;
    if (this->dim == 2){
        this->y += a;
    }
    return *this;
}
// P-=a (soustraction de a à chaque composante)
Point& Point::operator -=(const double& a)
{
    if (this->dim == 0){
        throw invalid_argument("Error: The vector is of dimension 0. Cannot perform subtraction.");
    }
    this->x -= a;
    if (this->dim == 2){
        this->y -= a;
    }
    return *this;
}
// P*=a
Point& Point::operator *=(const double& a)
{   
    if (this->dim == 0){
        throw invalid_argument("Error: The vector is of dimension 0. Cannot perform multiplication.");
    }
    this->x *= a;
    if (this->dim == 2){
        this->y *= a;
    }
    return *this;
}
// P/=a
Point& Point::operator /=(const double& a)
{
    if (this->dim == 0){
        throw invalid_argument("Error: The vector is of dimension 0. Cannot perform division.");
    }
    if (a == 0){
        throw invalid_argument("Error: Division by zero.");
    }
    this->x /= a;
    if (this->dim == 2){
        this->y /= a;
    }
    return *this;
}


// fonctions externes
//==========================================================================
// <<
ostream& operator <<(ostream& out, const Point& P)
{   
    if (P.dim == 0){
        throw invalid_argument("Error: The vector is of dimension 0.");
    }
    out<<"(";
    if (P.dim == 1){
        out<<P.x;
    }
    else if (P.dim == 2){
        out<<P.x<<","<<P.y;
    }
    out<<")";
    return out;
}
// +P
Point operator +(const Point& P)
{
    Point result = P;
    return result;
}
// -P
Point operator -(const Point& P)
{
    Point result = P;
    result *= -1;
    return result;
}
// P+Q 
Point operator +(const Point & P, const Point & Q)
{
    Point result = P;
    result += Q;
    return result;
}
// P-Q
Point operator -(const Point & P, const Point & Q)
{
    Point result = P;
    result -= Q;
    return result;
}
// P+a
Point operator +(const Point & P, double a)
{
    Point result = P;
    result += a;
    return result;
}
// a+P
Point operator +(double a, const Point & P)
{
    return P + a;
}
// P-a
Point operator -(const Point & P, double a)
{
    Point result = P;
    result -= a;
    return result;
}
// a-P
Point operator -(double a, const Point & P)
{
    return P - a;
}
// P*a
Point operator *(const Point & P, double a)
{
    Point result = P;
    result *= a;
    return result;
}
// a*P
Point operator *(double a, const Point & P)
{
    return P * a;
}
// P/a
Point operator /(const Point & P, double a)
{
    Point result = P;
    result /= a;
    return result;
}
// P==Q
bool operator ==(const Point & P, const Point & Q)
{
    if (P.dim != Q.dim || P.dim == 0 || Q.dim == 0){
        throw invalid_argument("Error: Vectors are of different sizes or one of the vector is of dimension 0. Cannot perform comparison.");
    }
    if (P.dim == 1){
        return P.x == Q.x;
    }
    else if (P.dim == 2){
        return P.x == Q.x && P.y == Q.y;
    }
    return false;
}
// P!=Q
bool operator !=(const Point & P, const Point & Q)
{
    return !(P == Q);
}
// P|Q
double operator |(const Point & P, const Point & Q)
{
    if (P.dim != Q.dim || P.dim == 0 || Q.dim == 0){
        throw invalid_argument("Error: Vectors are of different sizes or one of the vector is of dimension 0. Cannot perform scalar product.");
    }
    double result = 0;
    if (P.dim == 1){
        result += P.x * Q.x;
    }
    else if (P.dim == 2){
        result += P.x * Q.x + P.y * Q.y;
    }
    return result;
}
// |P|
double norme(const Point & P)
{ 
    return sqrt(P|P);
}
// mesure(A,B,C) = surface triangle ABC
double mesure(const Point & A, const Point & B, const Point & C)
{   
    if (A.dim != B.dim || A.dim != C.dim || A.dim == 0 || B.dim == 0 || C.dim == 0){
        throw invalid_argument("Error: Vectors are of different sizes or one of the vector is of dimension 0. Cannot perform scalar product.");
    }
    if (A.dim == 1 || B.dim == 1 || C.dim == 1){
        return 0.0; // Impossible de former un triangle en 1D
    }
    double mesured = 0.5 * std::abs(
        A.x * (B.y - C.y) +
        B.x * (C.y - A.y) +
        C.x * (A.y - B.y)
    );
    return mesured;
}



#endif // __POINT_CLASSE_HPP__