% on calcule le vecteur f du second membre 

% la fonction prend comme arguments : 
% - Nbpt = nombre de sommets 
% - Nbtri = nombre de triangle 
% - Coorneu(i) = coordonnées du sommet i
% - Refneu(i) = numéro de référence du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - tableau_resistance = les résistances sont sur les colonnes ordonnées en ligne selon (valeur, x, y) 
% - n = nombre de résistances 

function [f]=f_part1(Nbpt, Nbtri, Coorneu, Numtri, tableau_resistance,n)

    f=zeros(Nbpt,1);
    % boucle sur le nombre de triangles 
    for l=1:Nbtri 

        % coordonnées des sommets du triangle l
        x1 = Coorneu(Numtri(l,1), 1);
        y1 = Coorneu(Numtri(l,1), 2);

        x2 = Coorneu(Numtri(l,2), 1);
        y2 = Coorneu(Numtri(l,2), 2);

        x3 = Coorneu(Numtri(l,3), 1);
        y3 = Coorneu(Numtri(l,3), 2);

        sommetsTriangle=[x1,y1 ; x2,y2 ; x3,y3];

        % boucle sur le nombre de résistances 
        for j=1:n

            % on considère tableau_resistance colonne j ici  
            point = [tableau_resistance(2,j),tableau_resistance(3,j)];

            estAInterieur = estPointDansTriangle(point, sommetsTriangle);

            if estAInterieur
                bary=barycentre(point,Coorneu,Numtri,l);
                % si la résistance est dans le triangle l, 
                % on ajoute sa valeur pondérée à sa distance à chaque sommet à la Numtri(l,j)-ième coordonnée de f
                f(Numtri(l,1))=f(Numtri(l,1))+tableau_resistance(1,j)*bary(1);
                f(Numtri(l,2))=f(Numtri(l,2))+tableau_resistance(1,j)*bary(2);
                f(Numtri(l,3))=f(Numtri(l,3))+tableau_resistance(1,j)*bary(3);
            end 

        end 
        
    end 
    
 end