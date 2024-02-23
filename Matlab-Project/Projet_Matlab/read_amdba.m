function [Nbpt,Nbtri,Coorneu,Refneu,Numtri,Reftri]=read_amdba(nom_maillage);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% read_amdba:
% routine de lecture de fichiers de maillages triangulaires 2D au format 
% amdba. 
%
% SYNOPSIS [Nbpt,Nbtri,Coorneu,Refneu,Numtri,Reftri] = read_amdba(nom_maillage)
%          
% INPUT * nom_maillage : le nom d'un fichier de maillage au format amdba
%                   SANS SON SUFFIXE .amdba
%
% OUTPUT - Nbpt : nbre de sommets (entier) 
%        - Nbtri : nbre de triangles (entier)
%        - Coorneu : coordonnees (x, y) des sommets (matrice reelle Nbpt x 2)
%        - Refneu : reference des sommets (vecteur entier Nbpt x 1)
%        - Numtri : liste de triangles 
%                   (3 numeros de sommets - matrice entiere Nbtri x 3)
%        - Reftri : reference des triangles (matric entiere Nbtri x 1)
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ouverture du fichier et contrele
fid=fopen(sprintf('%s.amdba', nom_maillage),'r');
if (fid <=0 )
  error(sprintf('Le fichier de maillage : %s.amdba n''a pas ete trouve', ...
		nom_maillage));
end

% lecture sequentielle
N=fscanf(fid,'%i');
Nbpt=N(1);
Nbtri=N(2);
line=fgets(fid); % vide la fin de ligne

% lecteur des sommets 
tmp = fscanf(fid,'%f',[4,Nbpt]);
Coorneu=tmp(2:3,:)'; % la premiere colonne contient en fait le num du sommet
Refneu=tmp(4,:)';

% lecture des triangles
tmp = fscanf(fid,'%i',[5,Nbtri]);
Numtri=tmp(2:4,:)';
Reftri=tmp(5,:)';

% fermeture du fichier
fclose(fid);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        fin de la routine
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
