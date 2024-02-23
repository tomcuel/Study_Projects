%==========================================================
%Choix du maillage
%==========================================================
% Demander du nom du fichier, du maillage de four à traiter :
% - 'maillagegros.amdba'
% - 'maillagemoyen.amdba'
% - 'maillagefin.amdba'
fichier=input("nom du fichier (maillage) sous le format : 'nom_du_fichier' : ");


%===================================================================
%Obtention des données liées au maillage du four à partir du fichier
%===================================================================
[Nbpt,Nbtri,Coorneu,Refneu,Numtri,Reftri]=liremaillage(fichier);

%=============================================================
%Détail des données
%=============================================================
% Nbpt = nombre de sommets 
% Nbtri nombre de triangle 
% Coorneu(i) = coordonn300ées du sommet i
% Refneu(i) = numéro de référence du sommet i
% Numtri = tableau des triangles référencés avec les sommets correspondants 
% Reftri(i) = numéro de référence du triangle i


%==================================================================
%Affichage du nombre de triangles et du nombre de sommets / points
%==================================================================
disp("nombre de triangles :")
disp(Nbtri)
disp("nombre de sommets de triangle / points :")
disp(Nbpt)


%==================================================================
%Choix de la partie à traiter
%==================================================================
disp("1 : Problème direct")
disp("2 : Problème inverse")
disp("3 : Optimisation globale du four")
partie=input("choisir la partie que l'on veut traiter : ");


switch partie
    case 1
        % on résoud la partie 1 : problème direct
        % on cherche à calculer la température dans le maillage étant donné que l'on a :
            % - un maillage composé de triangles représentant de l'air et un pare-choc
            % - un certain nombre de résistances placées dans le maillage, de différentes valeurs 
            % - une température souhaitée dans le four
            % - une température au bord du four 
        probleme_direct(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, fichier);
        
    case 2 
        % on résout la partie 2 : problème inverse
        % on demande différentes choses à l'utilisateur : 
            % - un maillage composé de triangles représentant de l'air et un pare-choc
            % - un coefficient beta, nombre permettant de contrôler l'importance des termes à minimiser
            % - un certain nombre de résistances placées dans le maillage (avec une valeur de référence) 
            % - une température souhaitée dans le four (Topt)
            % - une température au bord du four
            
        % on cherche ensuite les coefficients pour connaître les valeurs des résistances 
        % qui permettent de s'approcher au mieux de la température optimal pour le pare-choc dans le four 
        probleme_inverse(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, fichier);
        
        
    case 3
        % on résout la partie 3 : 
        % on demande différentes choses à l'utilisateur : 
            % - un maillage composé de triangles représentant de l'air et un pare-choc
            % - une valeur de référence pour le calcul des résistances
            % - un nombre de résistances (nb_resistances)
            % - une température souhaitée dans le four (Topt)
            % - une température au bord du four
            % - un nombre de simulations à voir 
            
        % pour une simulation, le programme va choisir nb_resistances de manière aléatoire parmi les différents sommets 
        % en faisant attention à ne pas avoir des résistances en double ou sur le bord à chaque simulation
        
        % on cherche ensuite les coefficients pour connaître les valeurs de résistances 
        % qui permettent de s'approcher au mieux de la température optimale pour le pare-choc dans le four
        
        % on regarde ensuite quelle simulation minimise l'écart à la température optimal souhaitée
        probleme_doptimisation_du_four(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, fichier);
        
end 