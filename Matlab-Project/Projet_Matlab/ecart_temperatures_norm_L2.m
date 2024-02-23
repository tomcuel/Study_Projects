% calcul de l'écart entre notre température T et Topt pour la norme L2

% la fonction prend comme arguments : 
% - Nbtri = nombre de triangle 
% - Coorneu(i) = coordonnées du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - Reftri(i) = numéro de référence du triangle i
% - T = vecteur températures des différents sommets 
% - Topt = temperature voulue dans le pare-choc

function [ecart_norm_L2_de_temps]=ecart_temperatures_norm_L2(Nbtri, Coorneu, Numtri, Reftri, T, Topt)
    
    ecart_norm_L2_de_temps=0;
    % on regarde sur tous les triangles 
    for l=1:Nbtri 
        % on regarde si l'on est dans la pièce 
        if Reftri(l)==1
            
            M=kloccalc_part2_A(Coorneu, Numtri, l);

            for i=1:3
                for j=1:3
                    ecart_norm_L2_de_temps = ecart_norm_L2_de_temps + M(i,j)*(T(Numtri(l,i))-Topt)*(T(Numtri(l,j))-Topt);
                end
            end 

        end 
    end 
    
end 