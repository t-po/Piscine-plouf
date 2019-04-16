#include <iostream>
#include "graphe.h"

int main() {
    std::string id;
    graphe g{"..//files//broadway.txt","..//files//broadway_weights_0.txt"};
    g.afficher();                                                           ///Affiche le graphe



    return 0;
}