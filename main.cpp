#include <iostream>
#include "graphe.h"
#include "Svgfile.h"

int main() {
    Svgfile svgout;
    svgout.addGrid(100,true,"lightgrey");
    std::string id;
    graphe g{"../files/triville.txt","../files/triville_weights_0.txt"};
    g.afficher();///Affiche le graphe
    //g.afficher_graphe(svgout);
    std::cout<<std::endl<<std::endl<<"PRIM"<<std::endl;
    graphe* g2=g.prim();
    g2->afficher();
    g2->afficher_graphe(svgout);



    return 0;
}