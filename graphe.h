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

        ///Brute
        std::unordered_map< int,std::vector<float> > brute();
        bool *decToBinary(int n);
        bool connexite(std::vector< bool> b2);
        std::vector <float> poidsDuGraphe (std::vector <bool> b2);


        /// Prim
        graphe* prim();

        ///Pareto
        void pareto(std:: unordered_map<int,std::vector<float>> map_graphes);

        void trierAretesPourToutSommet();   ///Pour chaque sommet : trie le vecteur d'aretes relié au sommet

        bool estPresent( int ,std::unordered_map<int,sommet*>);

        void afficherAretePourToutSommet();

        void afficher_graphe(Svgfile& fic);
        //std::vector <float>poid_total();
    private:
        int m_ordre;
        int m_taille;
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<int ,sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,Arete*> m_aretes;
};


#endif //PISCINE_GRAPHE_H
