% on calcule le vecteur f du second membre 

% la fonction prend comme arguments : 
% - Nbpt = nombre de sommets 
% - Nbtri = nombre de triangle 
% - Coorneu(i) = coordonnées du sommet i
% - Refneu(i) = numéro de référence du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - res = coordonées de la résistance du plan : (x, y) 
% - A0 = valeur de la résistance

function [f]=f_part2(Nbpt, Nbtri, Coorneu, Numtri, res, A0)

    f=zeros(Nbpt,1);

    for l=1:Nbtri 

        % coordonnées des sommets du triangle l
        x1 = Coorneu(Numtri(l,1), 1);
        y1 = Coorneu(Numtri(l,1), 2);

        x2 = Coorneu(Numtri(l,2), 1);
        y2 = Coorneu(Numtri(l,2), 2);

        x3 = Coorneu(Numtri(l,3), 1);
        y3 = Coorneu(Numtri(l,3), 2);

        sommetsTriangle=[x1,y1 ; x2,y2 ; x3,y3];

        % la résistance est dans le triangle ??? 
        estAInterieur = estPointDansTriangle(res, sommetsTriangle);

        if estAInterieur
            bary=barycentre(res,Coorneu,Numtri,l);
            % si la résistance est dans le triangle l,
            % on ajoute sa valeur pondérée à sa distance à chaque sommet à la Numtri(l,j)-ième coordonnée de f
            f(Numtri(l,1))=f(Numtri(l,1))+A0*bary(1);
            f(Numtri(l,2))=f(Numtri(l,2))+A0*bary(2);
            f(Numtri(l,3))=f(Numtri(l,3))+A0*bary(3);
        end 
        
    end 
    
 end