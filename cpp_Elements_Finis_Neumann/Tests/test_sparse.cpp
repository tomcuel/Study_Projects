#include "../Src/sparse_classe.hpp"


typedef Vector<double> Vecteur;
typedef Sparse<double> Matrice;


int main()
{ 
    int n=10;
    Matrice M(n,n);
    for(int i=1;i<=n;i++){
        M(i,i)=2.;
        if(i>1) M(i,i-1)=-1;
        if(i<n) M(i,i+1)=-1;
    }
    //test affichage
    cout<<M<<endl;
    M.remplissage();
    //test opérations
    Matrice I(n,n);
    for (int i=1;i<=n;i++){
        I(i,i)=1.;
    }
    cout<<"\n(3.*M-2*I)/2 :"<<(3.*M-2.*I)/2.<<endl;
    Matrice T(n,n+1);
    for (int i=1;i<=n;i++){
        T(i,n+1)=i;
    }
    Matrice MT=M+T;
    cout<<"\nMT :"<<MT<<endl;
    MT.remplissage();


    //test produit Matrice * Vecteur
    Vecteur u(n);
    for (int i=0;i<n;i++){
        u[i]=i+1;
    }
    cout<<"\nu="<<u<<endl;
    cout<<"M*u="<<M*u<<endl;
    //test gradient conjugué
    Vecteur b=M*u;
    Vecteur x=gradConj(M,b,Vecteur(n),200);
    cout<<"x="<<x<<endl;
    cout<<"\n";


    return 0 ;
}

