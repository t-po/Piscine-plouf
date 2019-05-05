//
// Created by utilisateur on 21/04/2019.
//

#ifndef PISCINE_DIJKSTRAALGORITHM_H
#define PISCINE_DIJKSTRAALGORITHM_H
#include "graphe.h"
#include "DijkstraTable.h"

class DijkstraAlgorithm {

    public:
        DijkstraAlgorithm(graphe* graph);
        float dijkstra(int pointDeDepart, int pointFinal);
        DijkstraTable* Calculer(int pointSelectione, DijkstraTable* dijkstraTable);
        ValeurSommet* Find(std::vector<ValeurSommet*> tableau, int id);
        void CalculerDuSommet(int selectione, DijkstraTable* table);

    private:
        graphe* _graph;
};


#endif //PISCINE_DIJKSTRAALGORITHM_H
