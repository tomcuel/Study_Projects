% construction de la matrice Kmodifiée avec la condition sur le bord 

% la fonction prend comme arguments : 
% - Kmat = matrice du système linéaire du problème direct 
% - Nbpt = nombre de sommets 
% - Refneu(i) = numéro de référence du sommet i

function [Kmod]=Kmodifie(Nbpt, Refneu, Kmat)
    
    Kmod=sparse(Nbpt,Nbpt);
    % exploration des conditions sur chaque point 
    for i=1:Nbpt
        for j=1:Nbpt
            % coefficients diagonaux
            if i==j
                if Refneu(i)==3 
                    Kmod(i,i)=1; 
                else 
                    Kmod(i,i)=Kmat(i,i);
                end 

            end 
            
            % autres coefficients 
            if i ~=j && Refneu(i)~=3 && Refneu(j)~=3
                Kmod(i,j)=Kmat(i,j); 
            end

        end 
    end
end 