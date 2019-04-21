//
// Created by utilisateur on 21/04/2019.
//

#include "DijkstraTable.h"
#include "..\graphe.h"

DijkstraTable::DijkstraTable(graphe* graph) {

    Tableau =  InitialiseTable(graph->getMSommets());
    Tableau;
}

bool DijkstraTable::SommetsRestants() {

    for(auto sommet:Tableau){

        if(sommet->_ValeurOptimale.Calculer != true){
            return true;
        }
    }

    return false;
}

int DijkstraTable::ProchainSommet() {

    std::vector<ValeurSommet*> sommetsRestant;

    for(auto sommet:Tableau){

        if(sommet->_ValeurOptimale.Calculer != true){
            sommetsRestant.push_back(sommet);
        }
    }

    int valeurProchainSommet = -1;
    int prochainSommet = 0;

    for (auto sommet: sommetsRestant) {
        if(valeurProchainSommet == -1 || valeurProchainSommet > sommet->_ValeurOptimale.PoidMaximale){
            valeurProchainSommet = sommet->_ValeurOptimale.PoidMaximale;
            prochainSommet = sommet->Sommet;
        }
    }

    return prochainSommet;

}

std::vector<ValeurSommet*> DijkstraTable::InitialiseTable(std::unordered_map<int, sommet *> map) {

    std::vector<ValeurSommet*> tableau;

    for(auto ar:map){
        tableau.push_back(new ValeurSommet(ar.second));
    }

    return tableau;
}
