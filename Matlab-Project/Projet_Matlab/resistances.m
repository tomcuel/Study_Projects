% on ajoute à la main un tableau des résistances (les résistances sont sur les colonnes ordonnées en ligne selon (valeur, x, y)
% on peut rentrer pleins de résistances si l'on veut
% dans notre cas, on mettra pour les tests suivants : n=1, A=A0=10000, x=3/4, y=3/4


function[tableau_resistance]=resistances(n)
    k=n;
    tableau_resistance=zeros(3,n);
    while k>0 

        disp("resistance n°")
        disp(k)
        A=input("entrer la valeur d'une résistance : ");
        x=input("entrer l'abscisse d'une résistance : ");
        y=input("entrer l'ordonnée d'une résistance : ");
        tableau_resistance(:,k)=[A;x;y];
        k=k-1;

    end
     
end 
    