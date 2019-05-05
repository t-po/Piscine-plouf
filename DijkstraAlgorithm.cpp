//
// Created by utilisateur on 21/04/2019.
//

#include "DijkstraAlgorithm.h"




DijkstraAlgorithm::DijkstraAlgorithm(graphe* graph)  {
    _graph=graph;
}

float DijkstraAlgorithm::dijkstra(int pointDeDepart, int pointFinal) {

    auto tableau = Calculer(pointDeDepart, new DijkstraTable(_graph));

    return Find(tableau->Tableau, pointFinal)->_ValeurOptimale.PoidMaximale;

}

DijkstraTable* DijkstraAlgorithm::Calculer(int pointSelectione, DijkstraTable* dijkstraTable) {

    CalculerDuSommet(pointSelectione, dijkstraTable);

    if(dijkstraTable->SommetsRestants()){

        int prochainSommet = dijkstraTable->ProchainSommet();

        dijkstraTable = Calculer(prochainSommet, dijkstraTable);
    }

    return dijkstraTable;
}



ValeurSommet* DijkstraAlgorithm::Find(std::vector<ValeurSommet*> tableau, int id){

    for(auto valeur: tableau){
        if(valeur->Sommet == id){
            return valeur;
        }
    }
}

void DijkstraAlgorithm::CalculerDuSommet(int selectione, DijkstraTable* table){

    auto sommetSelection = _graph->getMSommets().find(selectione)->second;

    auto valeurBase = Find(table->Tableau, selectione);

    auto arets = sommetSelection->getMAretePourSommet();

    std::vector<sommet*> sommetsAdjacents;

    for(auto arete:arets){

        sommetsAdjacents.push_back(_graph->sommetSuivant(sommetSelection,arete));
    }


    for(auto sommet: sommetsAdjacents){


        ValeurSommet* valeur = Find(table->Tableau,sommet->getMId());

        if(valeur->_ValeurOptimale.Calculer == false){
            auto nouveauPoid = valeurBase->_ValeurOptimale.PoidMaximale + _graph->TrouvePoidsEntreDeuxSommets(sommet, sommetSelection);
            if(nouveauPoid < valeur->_ValeurOptimale.PoidMaximale || valeur->_ValeurOptimale.SommetPrecedent == 0){
                valeur->_ValeurOptimale.PoidMaximale = nouveauPoid;
                valeur->_ValeurOptimale.SommetPrecedent = selectione;
            }
        }
    }

    valeurBase->_ValeurOptimale.Calculer = true;

}