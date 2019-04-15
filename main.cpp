#include <iostream>
#include "graphe.h"

int main() {
    std::string id;
    graphe g{"../files/broadway.txt","../file/broadway_weights_0.txt"};
    g.afficher();                                                           ///Affiche le graphe
    std::cout<<"Veuillez choisir l'identifiant d'un sommet "<<std::endl;
    std::cin >> id;                                                   ///Applique le DFS et l'affiche
    /*int ncc=g.rechercher_afficherToutesCC();*/                            ///Variable non utilisé


    std::cout<<" "<<std::endl;
    std::cout<<"Le graphe est-il eulerien ?"<<std::endl<<std::endl;

    return 0;
}