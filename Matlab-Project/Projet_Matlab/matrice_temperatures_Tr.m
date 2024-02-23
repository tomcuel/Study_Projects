% On trouve ici les différents 0r que l'on calcule avec la résistance A0
% et qu'il faudra coefficenter avec les alpha_r plus tard dans le calcul

% la fonction prend comme arguments : 
% - Nbpt = nombre de sommets 
% - Nbtri = nombre de triangle 
% - Coorneu(i) = coordonnées du sommet i
% - Refneu(i) = numéro de référence du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - Reftri(i) = numéro de référence du triangle i
% - resistances = tableau des coordonnées des résistances 
% - nb_resistances = nombre de résistances
% - A0 = valeur de la résistance de base 
% - TD = température aux bords du four 

function [Temps]=matrice_temperatures_Tr(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, resistances, nb_resistances, A0, TD)
    
    % calcul de la matrice Kmat
    Kmat=matrice_K(Nbpt, Nbtri, Coorneu, Numtri, Reftri);

    % matrice des température des sommets pour chaque résistance 
    Temps=zeros(Nbpt,nb_resistances);
    % on fait le calcul à chaque fois comme s'il y avait qu'une seule résistance A0
    for i=1:nb_resistances
        xi=resistances(1,i);
        yi=resistances(2,i);
        res=[xi,yi];

        % on calcule le vecteur f du second membre 
        f=f_part2(Nbpt, Nbtri, Coorneu, Numtri,res, A0);

        td=vect_td(Nbpt, Refneu, TD);

        % calcul du second membre modifié
        secondmembremod=second_membre_mod_part2(Nbpt, Refneu, f, Kmat, td);

        % création de K modifiée selon si les sommets n° i et n°j sont sur le bord ou pas 
        Kmod=Kmodifie(Nbpt, Refneu, Kmat);

        % résolution de l'équation différentielle 
        Tr=Kmod\secondmembremod;
        Temps(:,i)=Tr;
        
    end 
end 