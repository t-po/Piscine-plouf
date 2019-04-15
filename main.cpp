#include <iostream>
#include "graphe.h"

int main() {
    std::string id;
    graphe g{"../files/broadway.txt","../file/broadway_weights_0.txt"};
    g.afficher();                                                           ///Affiche le graphe
    g.triKruskal();



    return 0;
}