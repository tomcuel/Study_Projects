% fonction qui regarde si les pondérations des résistances sont toutes positives
% elle renvoie 1 si c'est le cas, 0 sinon 

% la fonction prend comme arguments : 
% - alpha_m = vecteur de pondération des résistances
% - nb_resistances = nombre de résistances et taille de alpha_m

function [test]=resistance_positive(alpha_m, nb_resistances)
    test=1;
    for i=1:nb_resistances
        % si une pondération est négative, on change la valeur de test
        if alpha_m(i) < 0 
            test=0;
        end 
    end 

end 