%=================================================================
%Construction de la matrice d'assemblage de la matrice A
%=================================================================

% la fonction prend comme arguments : 
    % - Coorneu(i) = coordonnées du sommet i
    % - Numtri = tableau des triangles référencés avec les sommets correspondants 
    % - l = numéro du triangle considéré 

    
function [M]=kloccalc_part2_A(Coorneu, Numtri, l)

    % obtention des coordonnées des sommets du triangle l
    x1 = Coorneu(Numtri(l,1), 1);
    x2 = Coorneu(Numtri(l,2), 1);
    x3 = Coorneu(Numtri(l,3), 1);
    
    y1 = Coorneu(Numtri(l,1), 2);
    y2 = Coorneu(Numtri(l,2), 2);
    y3 = Coorneu(Numtri(l,3), 2);
    
    % tabx(i,j)=xi-xj
    tabx=[0 x1-x2 x1-x3;x2-x1 0 x2-x3; x3-x1 x3-x2 0];
    taby=[0 y1-y2 y1-y3;y2-y1 0 y2-y3; y3-y1 y3-y2 0];
    
    delta = tabx(2,3)*taby(3,1) - tabx(3,1)*taby(2,3);
    aire = abs(delta)/2;
    
    % en utilisant la formule de l'annexe 
    M=zeros(3,3);
    for i=1:3
        for j=1:3

            if i==j % si on a un lambda au carré 
                M(i,j)=aire*2*2/(4*3*2);
            else % sinon
                M(i,j)=aire*2/(4*3*2);
            end 

        end 
    end 

end 