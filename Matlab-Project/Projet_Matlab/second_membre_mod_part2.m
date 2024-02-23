% on calcule le second membre avec la condition modifiée sur le bord 

% la fonction prend comme arguments :
% - Nbpt = nombre de sommets 
% - Refneu(i) = numéro de référence du sommet i
% - f = première partie du second membre 
% - Kmat = matrice du système linéaire du problème direct 
% - td = vecteur température sur les bords du four

function [secondmembremod]=second_membre_mod_part2(Nbpt, Refneu, f, Kmat, td)
     % on a le second membre
     secondmembre=f-Kmat*td;

     % on construit le second membre modifié 
     secondmembremod=zeros(Nbpt,1);
     for i=1:Nbpt 
         if Refneu(i)==3 % Sommet i appartient au bord 
             secondmembremod(i)=0;
         end

         if Refneu(i)~=3 % Sommet i appartient au bord
             secondmembremod(i)=secondmembre(i);
         end 
     end

 end 