//
// Created by utilisateur on 21/04/2019.
//

#ifndef PISCINE_DIJKSTRATABLE_H
#define PISCINE_DIJKSTRATABLE_H


#include <vector>
#include "ValeurSommet.h"
#include "../graphe.h"

class DijkstraTable {


public:

    explicit DijkstraTable(graphe* graph);

    bool SommetsRestants();

    int ProchainSommet();


    std::vector<ValeurSommet*> Tableau;

    std::vector<ValeurSommet *> InitialiseTable(std::unordered_map<int, sommet* > map);
};


#endif //PISCINE_DIJKSTRATABLE_H
