//
// Created by utilisateur on 21/04/2019.
//

#ifndef PISCINE_VALEURSOMMET_H
#define PISCINE_VALEURSOMMET_H


#include <vector>
#include "ValeurOptimale.h"
#include "sommet.h"

class ValeurSommet {



public:

    ValeurOptimale _ValeurOptimale;
    int Sommet;
    ValeurSommet(sommet *pSommet);
};


#endif //PISCINE_VALEURSOMMET_H
