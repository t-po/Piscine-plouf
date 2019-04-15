//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_GRAPHE_H
#define PISCINE_GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"


class graphe {
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);

        ///Destructeur
        ~graphe();

        ///Affiche le graphe
        void afficher() const;

       void triKruskal();


    private:
        int m_ordre=0;
        int m_taille;
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<std::string,sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,arete*> m_aretes;
};


#endif //PISCINE_GRAPHE_H
