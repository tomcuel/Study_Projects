%==================================================================
%Savoir si un point est à l'intérieur d'un triangle
%==================================================================

% la fonction prend comme arguments : 
    % - point = un point du plan de type (x,y) 
    % - sommetsTriangle = matrice 3x2 des coordonnées des sommets du triangle considéré

    
function estAInterieur = estPointDansTriangle(point, sommetsTriangle)
    
    % coordonnées des sommets du triangle
    A = sommetsTriangle(1,:);
    B = sommetsTriangle(2,:);
    C = sommetsTriangle(3,:);
    
    
    % calcul des barycentres
    alpha = ((B(2)-C(2))*(point(1)-C(1)) + (C(1)-B(1))*(point(2)-C(2))) / ((B(2)-C(2))*(A(1)-C(1)) + (C(1)-B(1))*(A(2)-C(2)));
    
    beta = ((C(2)-A(2))*(point(1)-C(1)) + (A(1)-C(1))*(point(2)-C(2))) / ((B(2)-C(2))*(A(1)-C(1)) + (C(1)-B(1))*(A(2)-C(2)));
    
    gamma = 1 - alpha - beta;
    
    % vérification si les barycentres sont dans la plage [0, 1]
    estAInterieur = alpha >= 0 && beta >= 0 && gamma >= 0 && alpha <= 1 && beta <= 1 && gamma <= 1;
    
end
