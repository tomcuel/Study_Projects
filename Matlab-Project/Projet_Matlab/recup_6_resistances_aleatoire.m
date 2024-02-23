% fonction random qui donne 6 nombres entre 1 et Nbpt et refait si le nombre a déjà été tiré 
% pour trouver les coordonnées des 6 résistances 
% (tout en faisant attention à ce que la résistance ne soit pas sur le pare-chocs)

% la fonction prend comme arguments : 
% - Nbpt = nombre de sommets 
% - Nbtri = nombre de triangle 
% - Coorneu(i) = coordonnées du sommet i
% - Numtri = tableau des triangles référencés avec les sommets correspondants 
% - Reftri(i) = numéro de référence du triangle i
% - nb_resistance = nombre de résistances 

function [resistances]=recup_6_resistances_aleatoire(Nbpt, Nbtri, Coorneu, Numtri, Reftri, nb_resistances)
    resistances=zeros(2,nb_resistances);
    % compteur du nombre de résistances restantes à récupérer 
    r=nb_resistances;
    while r>0

        % générer un nombre aléatoire entre 1 et Nbpt
        numero=randi([1, Nbpt]);
        % ce point est un sommet d'un triangle
        x=Coorneu(Numtri(numero,1), 1);
        y=Coorneu(Numtri(numero,1), 2);
        point=[x;y];

        for l=1:Nbtri
            %coordonnées des sommets du triangle l
            x1 = Coorneu(Numtri(l,1), 1);
            y1 = Coorneu(Numtri(l,1), 2);

            x2 = Coorneu(Numtri(l,2), 1);
            y2 = Coorneu(Numtri(l,2), 2);

            x3 = Coorneu(Numtri(l,3), 1);
            y3 = Coorneu(Numtri(l,3), 2);

            sommetsTriangle=[x1,y1 ; x2,y2 ; x3,y3];
            estAinterieur=estPointDansTriangle(point,sommetsTriangle);
            % on regarde si on est dans le triangle
            if estAinterieur
                numero_tri=l;
            end 
        end 

        % si le triangle est dans l'air, on peut passer à une autre
        % résistance, sinon on réitère la demande pour placer cette
        % résistance
        if Reftri(numero_tri)==2 
            test=0;
            for q=1:nb_resistances
                % on ne veut pas une résistance déjà existante 
                if x==resistances(1,q) && y==resistances(2,q)
                    test=1;
                end 
                % on ne veut pas une résistance sur les bords du four
                if x==1 || x==-1 || y==1 || y==-1
                    test=1;
                end 
            end 
            if test==0
                resistances(:,r)=[x;y];
                r=r-1;
            end 
        end 
    end 