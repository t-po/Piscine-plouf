#include <iostream>
#include "graphe.h"
#include "Svgfile.h"
#include "DijkstraAlgorithm.h"

int main() {
    std:: unordered_map<int,std::vector<float>> map_graphes;
    Svgfile svgout;
    svgout.addGrid(100,true,"lightgrey");
    std::string id;
    graphe g{"../files/broadway.txt","../files/broadway_weights_0.txt"};
    g.afficher();///Affiche le graphe
    g.afficher_graphe(svgout);
    std::cout<<std::endl<<std::endl<<"PRIM"<<std::endl;
    graphe* g2=g.prim();
    g2->afficher();
    g2->afficher_graphe(svgout);
    map_graphes= g.brute();

    //g.pareto(map_graphes);
    graphe g3{"../files/broadway.txt","../files/broadway_weights_0.txt"};
    auto dijkstra = new DijkstraAlgorithm(&g3);
    auto resultat = dijkstra->dijkstra(1, 2);
    std::cout<<resultat;


    return 0;
}