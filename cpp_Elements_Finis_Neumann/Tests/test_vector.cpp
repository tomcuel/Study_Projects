#include "../Src/vector_classe.hpp"  


int main()
{
    cout<<"Test en réel : \n";
    Vector<double> V1; 
    cout<<"V1 = "<<V1<<endl;
    Vector<double> V2(3);
    cout<<"V2 = "<<V2<<endl;
    Vector<double> V3(3,1);
    cout<<"V3 = "<<V3<<endl;
    Vector<double> V4={1,2,3};
    cout<<"V4 = "<<V4<<endl;
    cout<<"V3+V4 = "<<V3+V4<<endl;
    cout<<"V3-V4 = "<<V3-V4<<endl;
    cout<<"V4*5 = "<<V4*5.<<endl;
    cout<<"5*V4 = "<<5.*V4<<endl;
    cout<<"(3.*V3+2.*V4)/2. = "<<(3.*V3-2.*V4)/2.<<endl;
    cout<<"-V4 = "<<-V4<<endl;
    cout<<"V3|V4 = "<<(V3|V4)<<endl;
    cout<<"norme(V4) = "<<norme(V4)<<endl;
    cout<<"V3==V4 ? : "<<(V3==V4?"V3=V4":"V3!=V4")<<endl;


    cout<<"\nTest en complexe : \n";
    complexe i(0.,1.);
    Vector<complexe> Z1(3,i);cout<<"Vecteur Z1 = "<<Z1<<endl;
    Vector<complexe> Z2(3,1);cout<<"Vecteur Z2 = "<<Z2<<endl;
    Vector<complexe> Z3(3);
    for (int j=1;j<=3;j++){
        Z3(j)=complexe(j);
    }
    cout<<"Vecteur Z3 : "<<Z3<<endl;
    Vector<complexe> Z=Z1+Z2-Z3;
    cout<<"Vecteur Z=Z1+Z2-Z3 : "<<Z<<endl;
    Z=i*Z1-Z2*i;cout<<"Vecteur Z=i*Z1-i*Z2 : "<<Z<<endl;
    cout<<"(Z1|Z2)="<<(Z1|Z2)<<endl;
    cout<<"norme(Z1)="<<norme(Z1)<<endl;


    cout<<"\nTest en Vector<Vector<double>> : \n";
    Vector<Vector<double>> M1(3,Vector<double>(3,1)); 
    cout<<"M1 = "<<M1<<endl;
    Vector<Vector<double>> M2={{1,2,3},{4,5,6},{7,8,9}}; 
    cout<<"M2 = "<<M2<<endl;
    cout<<"M1+M2 = "<<M1+M2<<endl;
    cout<<"M1-M2 = "<<M1-M2<<endl;
    cout<<"2*M2 = "<<2.*M2<<endl;


    cout<<"test vecteur réel -> vecteur complexe : \n ";
    Vector<complexe> ZR = Vector<double> (3,1);
    cout<<"ZR="<<ZR<<endl;  
    ZR=V4;
    cout<<" ZR="<<ZR<<endl;
    cout<<" ZR+Z2="<<ZR+Z2<<endl;
    cout<<"\n";


    return 0 ;
}
