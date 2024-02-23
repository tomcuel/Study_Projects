% on place/implémente les nb_resistances en créant un tableau de résistances
% on fait attention aussi à ce que ces résistances ne soient pas dans la zone du pare-choc mais dans la zone d'air 

% la fonction prend comme arguments : 
% - Nbtri = nombre de triangle 
% - Coorneu(i) = coordonnées du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - Reftri(i) = numéro de référence du triangle i
% - nb_resistances = nombre de résistances 

function [resistances]=placement_des_resistances(Nbtri, Coorneu, Numtri, Reftri, nb_resistances)

    resistances=zeros(2,nb_resistances);
    % compteur du nombre de résistances restantes à saisir 
    k=nb_resistances;
    while k>0 

        disp("resistance n°")
        disp(k)
        x=input("entrer l'abscisse d'une résistance : ");
        y=input("entrer l'ordonnée d'une résistance : ");
        point=[x,y];
        %on cherche dans quel triangle est ce point (x,y)

        for l=1:Nbtri
            %coordonnées des sommets du triangle l
            x1 = Coorneu(Numtri(l,1), 1);
            y1 = Coorneu(Numtri(l,1), 2);

            x2 = Coorneu(Numtri(l,2), 1);
            y2 = Coorneu(Numtri(l,2), 2);

            x3 = Coorneu(Numtri(l,3), 1);
            y3 = Coorneu(Numtri(l,3), 2);

            sommetsTriangle=[x1,y1 ; x2,y2 ; x3,y3];
            estAinterieur=estPointDansTriangle(point,sommetsTriangle);
            % on regarde si on est dans le triangle
            if estAinterieur
                numero_tri=l;
            end 
        end 

        % si le triangle est dans l'air, on peut passer à une autre résistance
        % sinon on réitère la demande pour placer cette résistance
        if Reftri(numero_tri)==2 
            resistances(:,k)=[x;y];
            k=k-1;
        else 
            disp("la résistance doit être dans l'air et pas dans le pare-choc, rentrer une nouvelle valeur de résistance : ")
        end 

    end
    disp("tableau des coordonnées des résistances")
    disp(resistances)
        
end 