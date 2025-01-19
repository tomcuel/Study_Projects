# Résolution d'une équation par la méthode des éléments finis en C++
>  Un peu comme cela été fait dans le cadre d'un projet Matlab plus tôt dans l'année, mais ici en utilisant le langage C++ afin de permettre une résolution en théorie plus rapide, à l'occasion de l'introduction à la programmation scientifique dans un cours, d'une équation de Neumann

## Path tree
```
cpp_Elements_Finis_Neumann/
├── Data/                           # résultats et maillages sous format .in
│
├── Src/                            # différentes classes et parties du code 
│   ├── elements_finis_classe.hpp   # calcul des 
│   ├── maillage_classe.hpp         # gestion de maillages 1D ou 2D
│   ├── neumann_classe.hpp          # résolution de l'équation
│   ├── point_classe.hpp            # gestion de points 1D ou 2D
│   ├── sparse_classe.hpp           # gestion des matrices creuses en utilisant des map
│   └── vector_classe.hpp           # gestion des vecteurs 
│
└── Tests/                          # tests effectués pour vérifier le bon fonctionnement de chaque classe
```

## Analyse des résultats 
Il n'y a pas d'analyse des résultats, mais seulement des fichiers .in qui sont créés et qui peuvent être ensuite utilisé dans Matlab ou en Python pour tracer les résultats 

## Structures des codes 
```cpp
//==========================================================================
// classe définissant … 
//==========================================================================
#ifndef __NOM_CLASSE_HPP__
#define __NOM_CLASSE_HPP__


#include 
typedef 



//==========================================================================
//classe …
//==========================================================================
class …
{
public:
    // déclarations des fonctions membres     
};


// fonctions membres
//==========================================================================
// implémentation des fonctions membres 


// fonctions externes
//==========================================================================
// implémentation des fonctions externes 


//==========================================================================
//classe … héritant de la classe précédente
//==========================================================================
class … : public …
{
public:
    // déclarations des fonctions membres     
};


// fonctions membres
//==========================================================================
// implémentation des fonctions membres 


// fonctions externes
//==========================================================================
// implémentation des fonctions externes 



#endif // __NOM_CLASSE_HPP__
```