#include <iostream>
#include "graphe.h"
#include "Svgfile.h"

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
    g.pareto(map_graphes);


    return 0;
}
