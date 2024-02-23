% on regarde ici l'obtention de la température dans le four dans le cas où
% diverses résistances sont placées.
% les valeurs des résistances sont les mêmes au départ 
% on cherche alors la pondération de ces valeurs qui va permettre de se rapprocher le plus possible 
% de la température optimale que l'on souhaite pour le pare-choc dans le four 

% la fonction prend comme arguments : 
    % - Nbpt = nombre de sommets 
    % - Nbtri = nombre de triangle 
    % - Coorneu(i) = coordonnées du sommet i
    % - Refneu(i) = numéro de référence du sommet i
    % - Numtri = tableau des triangles référencés avec les sommets correspondants 
    % - Reftri(i) = numéro de référence du triangle i
    % - fichier = nom du maillage du four que l'on étudie

    
    
function probleme_inverse(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, fichier)

    %========================================================================
    %Demande des donneés à l'utilisateur
    %========================================================================
    % nombre β permettant de contrôler l'importance des termes à minimiser
    beta=input("donner le nombre β : ");
    % il sera entre 10^-5 et 10^-2
    
    % Température que l'on souhaite obtenir pour le pare-choc
    Topt=input("entrer la température du pare-chocs souhaitée : "); 

    % entrée de la température sur les bords du four (qui sera de 300K)
    TD=input("entrer la température des bords du four : ");
    
    % on crée aussi le vecteur colonne de la température des bords du four 
    % T0 pour le problème direct avec 0 résistance
    % équivalent à un vecteur température de 300 de partout, d'où 
    T0=zeros(Nbpt,1);
    for i=1:Nbpt
        T0(i)=TD;
    end 

    
    %=================================================================
    %Création du tableau de l'emplacement des résistances
    %=================================================================
    % valeur de la résistance nous servant d'échelonnage
    A0=input("résistance de base : ");
    disp("résistance de base : ")
    disp(A0)
    
    
    % on doit avoir 6 résistances comme inconnues dans un tableau qui va se présenter la forme suivante : 
    % à la colonne i, on a les coordonnées (xi,yi) 
    nb_resistances=input("nombres de résistances souhaitées : ");
    resistances=placement_des_resistances(Nbtri, Coorneu, Numtri, Reftri, nb_resistances);
    % test avec (3/4,3/4) (1/2 1/2) (2/3 2/3) (-2/3 -2/3) (3/4 -3/4) (-3/4 3/4) qui donne qqch d'assez concluant

    
    %=================================================================
    %Construction de la matrice des températures
    %=================================================================
    % On trouve ici les différents θr que l'on calcule avec la résistance A0
    % et qu'il faudra coefficenter avec les alpha_r plus tard dans le calcul
    matrice_temperatures=matrice_temperatures_Tr(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, resistances, nb_resistances, A0, TD);
    

    
    %=================================================================
    %Construction de la matrice A
    %=================================================================
    A=matrice_A(Nbtri, Coorneu, Numtri, Reftri, beta, matrice_temperatures, nb_resistances);
   

    
    %=================================================================
    %Création du vecteur différence entre la température voulue 
    %et celle des parois du four (Topt-TD)
    %=================================================================
    Tb=Topt-TD;
    
    
    %=================================================================
    %Construction du vecteur b
    %=================================================================
    b=vect_b(Nbtri, Coorneu, Numtri, Reftri, Tb, matrice_temperatures, nb_resistances);
    
    
    %=================================================================
    %Résolution du système
    %=================================================================
    alpha_m=A\b;

    
    %=================================================================
    %Calcul de la température en prenant en compte la pondération des
    %résistances
    %=================================================================
    T=T0;
    for i=1:nb_resistances
        T=T+alpha_m(i)*matrice_temperatures(:,1);
    end 
    
    
    %=================================================================
    %Affichage du maillage en couleur
    %=================================================================
    affichemaillage(fichier,'titre',T);
    
    %=================================================================
    %Calcul de la norme L2 de alpha_m
    %=================================================================
    norm_alpha_m=norm(alpha_m,2);
    disp("norme sur L2 de alpha_m")
    disp(norm_alpha_m)

    
    %=================================================================
    %Calcul de l'écart de température en norme L2
    %=================================================================
    ecart_norm_L2_de_temperatures=ecart_temperatures_norm_L2(Nbtri, Coorneu, Numtri, Reftri, T, Topt);
    disp("norme L2 d'écart de température avec Topt")
    disp(ecart_norm_L2_de_temperatures)

  
    
    
    

end 
