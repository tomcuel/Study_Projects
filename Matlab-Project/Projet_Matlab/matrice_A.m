%=================================================================
%Construction de la matrice A
%=================================================================

% la fonction prend comme arguments : 
    % - Nbtri = nombre de triangle 
    % - Coorneu(i) = coordonnées du sommet i
    % - Numtri = tableau des triangles référencés avec les sommets correspondants 
    % - Reftri(i) = numéro de référence du triangle i
    % - beta = nombre permettant de contrôler l'importance des termes à minimiser
    % - matrice_temperatures = matrice des températures pour chaque résistance, toujours de valeurs A0
    % - nb_resistances = nombre de résistances 

    
function [A]=matrice_A(Nbtri, Coorneu, Numtri, Reftri, beta, matrice_temperatures, nb_resistances)
    
    % la matrice des beta*δrr'
    A=beta*eye(nb_resistances);
    
    % chaque triangle dans omega_p va ajouter des valeurs à A liées aux températures trouvées précédements
    for l = 1 : Nbtri
        if Reftri(l)==1        % on regarde si on est dans le pare-choc

            % matrice d'assemblage de A
            M=kloccalc_part2_A(Coorneu, Numtri, l);     %Matrice locale

            % assemblage de A 
            for r = 1 : nb_resistances
                for s = 1 : nb_resistances
                    for i = 1 : 3
                        for j = 1 : 3
                            A(r,s) = A(r,s) + M(i,j)*matrice_temperatures(Numtri(l,i),r)*matrice_temperatures(Numtri(l,j),s);
                        end
                    end
                end
            end

        end 
    end
        
end 
       