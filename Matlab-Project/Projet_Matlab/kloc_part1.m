%==================================================================
%Construction de la matrice d'assemblage de K
%==================================================================

% la fonction prend comme arguments : 
    % - Coorneu(i) = coordonnées du sommet i
    % - Numtri = tableau des triangles référencés
    %            avec les sommets correspondants 
    % - l = numéro du triangle considéré
    % - ka = coefficient dépendant du milieu dans lequel est le triangle

function [mat]=kloc_part1(Coorneu, Numtri, l, ka)
    
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
    
    % on suit la méthode de calcul de la partie théorique 
    delta = tabx(2,3)*taby(3,1) - tabx(3,1)*taby(2,3);
    deltainv = 1/delta;
    aire = abs(delta)/2;
    
    grad = [taby(2, 3), -tabx(2, 3); taby(3, 1), -tabx(3, 1); 
            taby(1, 2), -tabx(1, 2)];
    grad = grad * deltainv;
    
    mat = aire * ka * (grad * grad');
    
    end 