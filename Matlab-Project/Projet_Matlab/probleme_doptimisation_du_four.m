% pour une simulation, le programme va choisir nb_resistances de manière aléatoire parmi les différents sommets 
% en faisant attention à ne pas avoir des résistances en double ou sur le bord à chaque simulation : 
% on cherche ensuite les coefficients pour connaître les valeurs de résistances 
% qui permettent de s'approcher au mieux de la température optimal pour le pare-choc dans le four
% on regarde ensuite quelle simulation minimise l'écart à la température optimal souhaitée


% la fonction prend comme arguments : 
    % - Nbpt = nombre de sommets 
    % - Nbtri = nombre de triangle 
    % - Coorneu(i) = coordonnées du sommet i
    % - Refneu(i) = numéro de référence du sommet i
    % - Numtri = tableau des triangles référencés avec les sommets correspondants 
    % - Reftri(i) = numéro de référence du triangle i
    % - fichier = nom du maillage du four que l'on étudie

function probleme_doptimisation_du_four(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, fichier);

    beta=0.0001
    
    % c'est la température que l'on souhaite obtenir pour le pare-choc
    Topt=input("entrer la température du pare-chocs souhaitée : "); 

    % entrée de la température sur les bords du four (qui sera de 300K)
    TD=input("entrer la température des bords du four : ");
    
    % on fait aussi le vecteur colonne de la température des bords du four 
    % T0 pour le problème direct avec 0 résistance
    % équivalent à un vecteur température de 300 de partout, d'où 
    T0=zeros(Nbpt,1);
    for i=1:Nbpt
        T0(i)=TD;
    end 

    % valeur de la résistance nous servant d'échelonnage
    A0=input("résistance de base : ");
    disp("résistance de base : ")
    disp(A0)

    % nombre de configuration de placements de résistances à tester
    nb_config_testees=input("nombre de configuration que vous voulez tester : ");
    disp("nombre de configurations à tester")
    disp(nb_config_testees)
    
    % nombres de résistance à placer dans le four 
    nb_resistances=input("nombres de résistances souhaitées : ");
    disp("nombres de résistances souhaitées : ")
    disp(nb_resistances)
    
    % tableau des résistances mis à zéro avec les bonnes dimensions
    meilleure_tableau_resistances=zeros(2,nb_resistances);
    % meilleure température sur les configurations testées 
    meilleure_temperatures=zeros(Nbpt,1);
    % meilleure norme, la plus petite, on commence avec une valeur haute pour être sur de passer en dessous 
    meilleure_norme=100000000;
    % coefficient de pondération des résistances qui minimise l'écart de températures 
    meilleur_alpha=zeros(Nbpt,1);
    
    % on boucle sur les configurations à tester
    k=nb_config_testees;
    while k>0
        % on doit avoir 6 résistances comme inconnues dans un tableau qui va se présenter la forme suivante : 
        % à la colonne i, on a les coordonnées (xi,yi) 

        % fonction random qui :
            % donne 6 nombres entre 1 et Nbpt
            % refait si le nombre a déjà été tiré 
            % fait attention à ce que la résistance ne soit pas sur le pare-choc
        resistances=recup_6_resistances_aleatoire(Nbpt, Nbtri, Coorneu, Numtri, Reftri, nb_resistances);
        
        
        %===================================================================
        %Recherche des différents θr que l'on calcule avec la résistance A0
        %===================================================================
        % il faudra ensuite les coefficenter avec les α_r
        matrice_temperatures=matrice_temperatures_Tr(Nbpt, Nbtri, Coorneu, Refneu, Numtri, Reftri, resistances, nb_resistances, A0, TD);

        
        %==========================================================
        %Construction de la matrice A
        %==========================================================
        A=matrice_A(Nbtri, Coorneu, Numtri, Reftri, beta, matrice_temperatures, nb_resistances);
        
        
       %=======================================================================================
        %Création du vecteur différence entre la température voulue et celle des parois du four
        %=======================================================================================
        Tb=Topt-TD;
        
        
        %==========================================================
        %Construction du vecteur b
        %==========================================================
        b=vect_b(Nbtri, Coorneu, Numtri, Reftri, Tb, matrice_temperatures, nb_resistances);
        
        
        %==========================================================
        %Résolution du système
        %==========================================================
        alpha_m=A\b;
        
        %==========================================================
        %Vérification de la positivité des résistances 
        %==========================================================
        % on incrémente k que lorsqu'on a visité une configuration valable 
        if resistance_positive(alpha_m, nb_resistances)==1
            %============================================================================
            %Calcul de la température en prenant en compte la pondération des résistances 
            %============================================================================
            T=T0;
            for i=1:nb_resistances
                T=T+alpha_m(i)*matrice_temperatures(:,1);
            end 


            %============================================================
            %Calcul de la norme2 de T-Topt
            %============================================================
            norm2_temp=ecart_temperatures_norm_L2(Nbtri, Coorneu, Numtri, Reftri, T, Topt);

            %============================================================================
            %Comparaison de cette configuration avec celle qui minimise le plus la norme
            %============================================================================ 
            if norm2_temp < meilleure_norme
                meilleure_temperatures=T;
                meilleure_norme=norm2_temp;
                meilleure_tableau_resistances=resistances;
                meilleur_alpha=alpha_m;
            end 
            
            k=k-1;
        end 
        
    end 
    
    
    % on affiche des résultats, on affiche aussi le maillage 
    %disp("parmi les différentes configurations testées, le vecteur température qui minimise la fonctionnelle est : ")
    %disp(meilleure_temperatures)
    affichemaillage(fichier,'titre',meilleure_temperatures);
    disp("meilleur répartition des résistances")
    disp(meilleure_tableau_resistances)
    disp("meilleur alpha, pondération des résistances")
    disp(meilleur_alpha)
    disp("norme associée")
    disp(meilleure_norme)
    disp("nombre de configurations testées")
    disp(nb_config_testees)
      

end 