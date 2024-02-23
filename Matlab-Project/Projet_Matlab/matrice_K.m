%==================================================================
%Calcul de Kmat
%==================================================================

% la fonction prend comme arguments : 
    % - Nbpt = nombre de sommets 
    % - Nbtri = nombre de triangle 
    % - Coorneu(i) = coordonnées du sommet i
    % - Numtri = tableau des triangles référencés avec les sommets correspondants 
    % - Reftri(i) = numéro de référence du triangle i

    
function[Kmat]=matrice_K(Nbpt, Nbtri, Coorneu, Numtri, Reftri)

    % elle est vide d'après ce qu'on fait dans la partie théorique 
    Kmat = sparse(Nbpt, Nbpt);
    for l=1:Nbtri
        
        % on regarde si le triangle est dans le pare-choc ou dans l'aire
        if Reftri(l)==2
            ka=1;
        end 
        if Reftri(l)==1
            ka=10;
        end 
        
        % matrice locale utilisée pour la procédure d'assemblage de K
        kloc = kloc_part1(Coorneu, Numtri, l, ka);

        % procédure d'assemblage de K
        for k = 1 : 3
            i = Numtri(l,k);
            for m = 1 : 3
                j = Numtri(l,m);
                Kmat(i,j)=Kmat(i,j)+kloc(k,m);
            end
        end
    end 
end 