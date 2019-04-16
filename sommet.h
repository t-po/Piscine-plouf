//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_SOMMET_H
#define PISCINE_SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "arete.h"


class sommet {
    public:
        ///constructeur qui reçoit en params les données du sommet
        sommet(int,double,double);
        ~sommet();
        void ajouterVoisin(const sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        int getDegre();
        void ajouterAretes(const arete*);
        void trierAretes();     ///Trie les aretes relié au sommet dans l'ordre croissant de la première pondérations.

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const sommet*> m_voisins;
        std::vector<const arete*> m_arete;

        /// Données spécifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position
};


#endif //PISCINE_SOMMET_H
