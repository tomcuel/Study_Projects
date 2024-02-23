% on calcule les coordonnées barycentriques pour un point (x, y) à l'intérieur du triangle numéro l

% la fonction prend comme arguments : 
% - point = un point du plan de type (x,y) 
% - Coorneu(i) = coordonnées du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - l = numéro du triangle que l'on considère ici

function[poids]=barycentre(point,Coorneu,Numtri,l)
    x=point(1);
    y=point(2);

    x1 = Coorneu(Numtri(l,1), 1);
    y1 = Coorneu(Numtri(l,1), 2);
    
    x2 = Coorneu(Numtri(l,2), 1);
    y2 = Coorneu(Numtri(l,2), 2);
    
    x3 = Coorneu(Numtri(l,3), 1);
    y3 = Coorneu(Numtri(l,3), 2);
        
    % on calcule les coordonnées barycentriques pour un point (x, y) à l'intérieur du triangle (x1, y1), (x2, y2), (x3, y3)

    % on calcul des déterminants
    detT = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);
    alpha = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / detT;
    beta = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / detT;
    gamma = 1 - alpha - beta;

    % on a les poids correspondants à chaque sommet du triangle
    poids = [alpha, beta, gamma];
    
end 