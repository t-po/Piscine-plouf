#include <iostream>
#include "graphe.h"
#include "Svgfile.h"
#include "DijkstraTableObjects/DijkstraAlgorithm.h"

int main() {
    Svgfile svgout;
    svgout.addGrid(100,true,"lightgrey");
    std::string id;
    graphe g{"../files/broadway.txt","../files/broadway_weights_0.txt"};
    std::cout<<"0"<<std::endl;
    g.afficher();///Affiche le graphe
    std::cout<<"1"<<std::endl;
    //g.afficher_graphe(svgout);
    //std::cout<<std::endl<<std::endl<<"PRIM"<<std::endl;
    graphe* g2=g.prim();
    //g2->afficher();
    //g2->afficher_graphe(svgout);
    graphe g3{"../files/broadway.txt","../files/broadway_weights_0.txt"};
    auto dijkstra = new DijkstraAlgorithm(&g3);
    auto resultat = dijkstra->dijkstra(1, 2);
    std::cout<<resultat;



    return 0;
}