#include <iostream>
#include "graphe.h"

int main() {
    std::string id;
    graphe g{"..//files//manhattan.txt","..//files//manhattan_weights_0.txt"};
    g.afficher();///Affiche le graphe
    std::cout<<std::endl<<std::endl<<"PRIM"<<std::endl;
    graphe* g2=g.prim();
    g2->afficher();



    return 0;
}