function affichemaillage(nom_maillage, titre,T);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % affichemaillage: 
    % pour visualiser un maillage triangulaire 2D
    %
    % SYNOPSIS affichemaillage(nom_maillage, titre)
    %          
    % INPUT  * nom_maillage : racine du fichier de maillage .amdba (string) 
    %        * titre (optionel) un titre (string)
    %
    % OUTPUT une fenetre graphique
    %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    % control on the input args
    if (nargin<2), titre = ''; end;

    % lecture du fichier nom_maillage.amdba
    [Nbpt,Nbtri,Coorneu,Refneu,Numtri,Reftri]=liremaillage(nom_maillage);

    %visualisation du maillage
    figure;
    hold on

    % maillage
    trisurf(Numtri,Coorneu(:,1),Coorneu(:,2),T);
    view(2);
    axis('equal');

    % ajouter eventuellement un titre
    title(nom_maillage);

    hold off;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %                                                        fin de la routine
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
end
