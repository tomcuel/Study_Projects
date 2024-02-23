% on regarde ici l'obtention de la température dans le four dans le cas où diverses résistances sont placées 

% la fonction prend comme arguments : 
    % - Nbpt = nombre de sommets 
    % - Nbtri = nombre de triangle 
    % - Coorneu(i) = coordonnées du sommet i
    % - Refneu(i) = numéro de référence du sommet i
    % - Numtri = tableau des triangles référencés avec les sommets correspondants 
    % - Reftri(i) = numéro de référence du triangle i
    % - fichier = nom du maillage du four que l'on étudie


function probleme_direct(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, fichier)

    %==================================================================
    %Calcul de Kmat
    %==================================================================
    Kmat=matrice_K(Nbpt, Nbtri, Coorneu, Numtri, Reftri);

    
    
    %==================================================================
    %Prise en compte des résistances
    %==================================================================
    n=input("donner le nombre de résistances : ");
    tableau_resistance=resistances(n);
    disp("tableau des résistances")
    disp(tableau_resistance)
    

    %==================================================================
    %Calcul du second membre
    %==================================================================
    % on calcule le vecteur f du second membre 
    f=f_part1(Nbpt, Nbtri, Coorneu, Numtri, tableau_resistance,n);

    
    %==================================================================
    %Choix de la température de la pièce
    %==================================================================
    % entrée de la température sur les bords du four (qui sera de 300K)
    TD=input("entrer la température des bords du four: ");
    td=vect_td(Nbpt, Refneu, TD);

    
    %==================================================================
    %Modification du second membre
    %==================================================================
    % calcul du second membre modifié
    secondmembremod=second_membre_mod_part1(Nbpt, Refneu, f, Kmat, td, TD);

    
    %==================================================================
    %Modification de K
    %==================================================================
    % création de K modifiée selon si les sommets n° i et n°j sont sur le bord ou pas 
    Kmod=Kmodifie(Nbpt, Refneu, Kmat);

    
    %==================================================================
    %Résolution de l'équation différentielle
    %================================================================== 
    T0=Kmod\secondmembremod;

    
    %==================================================================
    %Affichage du maillage en couleur 
    %================================================================== 
    affichemaillage(fichier,'titre',T0);

    
    %==================================================================
    %Obtention de la température maximale dans le four 
    %==================================================================  
    max = temperature_max(T0, Nbpt);
    disp("température max")
    disp(max)
    

end

% on trouve en max des températures pour l'exemple avec la résistance de 10000 en (3/4,3/4) : 
% - gros : 3.8683e+03
% - moyen : 5.0405e+03
% - fin : 5.8796e+03