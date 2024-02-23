% donne les différentes données lié à ce maillage de four 
% la fonction prend comme arguments : 
% - fichier = nom du maillage du four que l'on étudie

function [Nbpt,Nbtri,Coorneu,Refneu,Numtri,Reftri]=liremaillage(nomfile) 
    fid = fopen(nomfile,'r') ;
    N = fscanf(fid,'%i') ;
    Nbpt = N(1) ;
    Nbtri = N(2) ;
    line = fgets(fid) ;
    tmp = fscanf(fid,'%f',[4,Nbpt]) ; 
    Coorneu = tmp(2:3,:)' ;
    Refneu = tmp(4,:)' ;
    tmp = fscanf(fid,'%i',[5,Nbtri]) ; 
    Numtri=tmp(2:4,:)' ; 
    Reftri=tmp(5,:)' ;
end 

%Pour lire un maillage de type .ambda 