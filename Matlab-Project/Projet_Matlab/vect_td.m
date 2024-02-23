% on calcule le vecteur température à l'état initial du four

% la fonction prend comme arguments : 
% - Nbpt = nombre de sommets 
% - Refneu(i) = numéro de référence du sommet i
% - TD = température sur les bords du four 

function [td]=vect_td(Nbpt, Refneu,TD)
     td=zeros(Nbpt,1);
     % on cherche pour chaque , si le point i est sur le bord, ie Refneu(i)=3
     for i=1:Nbpt 
         if Refneu(i)==3 % Sommet i appartient au bord 
             td(i)=TD;
         end 
     end 
end 