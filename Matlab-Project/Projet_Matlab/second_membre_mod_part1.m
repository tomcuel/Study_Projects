% on calcule le second membre avec la condition modifiée sur le bord 

% la fonction prend comme arguments :
% - Nbpt = nombre de sommets 
% - Refneu(i) = numéro de référence du sommet i
% - f = première partie du second membre 
% - Kmat = matrice du système linéaire du problème direct 
% - td = vecteur température sur les bords du four
% - TD = température aux bords du four  

function [secondmembremod]=second_membre_mod_part1(Nbpt, Refneu, f, Kmat, td, TD)
     % on a le second membre
     secondmembre=f-Kmat*td;

     % on construit le second membre modifié avec la condition sur le bord 
     secondmembremod=zeros(Nbpt,1);
     for i=1:Nbpt 
         if Refneu(i)==3 % Sommet i appartient au bord 
             secondmembremod(i)=TD;
         end

         if Refneu(i)~=3 % Sommet i appartient au bord
             secondmembremod(i)=secondmembre(i);
         end 
     end

 end 