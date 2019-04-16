#include <iostream>
#include "graphe.h"
#include "Svgfile.h"

int main() {
    void svgTest();
    Svgfile svgout;
    svgout.addGrid(100,true,"lightgrey");
    std::string id;
    graphe g{"../files/broadway.txt","../files/broadway_weights_0.txt"};
    g.afficher();                                                           ///Affiche le graphe
    std::cout<<"Veuillez choisir l'identifiant d'un sommet "<<std::endl;
    std::cin >> id;                                                   ///Applique le DFS et l'affiche
    /*int ncc=g.rechercher_afficherToutesCC();*/                            ///Variable non utilisé


    std::cout<<" "<<std::endl;
    std::cout<<"Le graphe est-il eulerien ?"<<std::endl<<std::endl;

    return 0;
}


void svgTest()
{
    /// Sortie graphique dans le fichier output.svg
    /// ( options à voir svgfile.h ligne 23 )
    Svgfile svgout;

    /// Dessin du repère cartésien
    svgout.addGrid();
    /// Dessins de sphères
    svgout.addDisk(100, 100, 90, "redball");
    svgout.addDisk(300, 100, 70, "greenball");
    svgout.addDisk(500, 100, 50, "blueball");
    svgout.addDisk(700, 100, 30, "greyball");
    /// Dessins de disques
    svgout.addDisk(100, 300, 30, "red");
    svgout.addDisk(300, 300, 50, "green");
    svgout.addDisk(500, 300, 70, "blue");
    svgout.addDisk(700, 300, 90, "grey");
    /// Dessins de croix
    svgout.addCross(300, 300, 50);
    for (int y=50; y<400; y+=50)
        svgout.addCross(400, y, 15);
    /// L'objet svgout est automatiquement libéré à la sortie
    /// de ce sous-programme : le fichier output.svg est alors fermé
}