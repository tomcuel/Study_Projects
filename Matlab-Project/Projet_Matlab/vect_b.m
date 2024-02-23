% construction du vecteur b

% la fonction prend comme arguments : 
% - Nbtri = nombre de triangle 
% - Coorneu(i) = coordonnées du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - Reftri(i) = numéro de référence du triangle i
% - Tb = vecteur différence entre la température voulue et celle des parois du four (Topt-TD)
% - matrice_temperatures = matrice des températures pour chaque résistance, toujours de valeurs A0
% - nb_resistances = nombre de résistances 

function [b]=vect_b(Nbtri, Coorneu, Numtri, Reftri, Tb, matrice_temperatures, nb_resistances)
    
    % la matrice des beta*symbole_kronecker_r_r'
    b=zeros(nb_resistances,1);
    for l = 1 : Nbtri
        % on regarde si on est dans le pare-choc
        if Reftri(l)==1
            
            % vecteur d'assemblage de d
            M=kloccalc_part2_b(Coorneu, Numtri, l);

            % assemblage de b 
            for r = 1 : nb_resistances
                for j = 1 : 3
                    b(r) = b(r) + M(j)*matrice_temperatures(Numtri(l,j),r)*Tb;
                end
            end
            
        end 
    end
        
end 
       