//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_GRAPHE_H
#define PISCINE_GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "Arete.h"
#include "Svgfile.h"


class graphe {
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);
        graphe(int mtaille, int mordre,  std::unordered_map<int,sommet*> msommets,std::unordered_map<int,Arete*> maretes);

        ///Destructeur
        ~graphe();

        ///Affiche le graphe
        void afficher() const;
        graphe* prim();
        void trierAretesPourToutSommet();   ///Pour chaque sommet : trie le vecteur d'aretes relié au sommet
        bool estPresentMap(int, std::unordered_map<int, sommet *>);
        bool estPresentVector(int,std::vector<Arete*>);
        void afficherAretePourToutSommet();
        void afficher_graphe(Svgfile& fic);
        //std::vector <float>poid_total();
        float dijkstra(int i);
        float calculPr2();
    private:
        int m_ordre;
        int m_taille;

        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<int ,sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,Arete*> m_aretes;
};


#endif //PISCINE_GRAPHE_H
