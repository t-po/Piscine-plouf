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


class sommet {
    public:
        ///constructeur qui reçoit en params les données du sommet
        sommet(std::string,double,double);
        ~sommet();
        void ajouterVoisin(const sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        int getDegre();

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const sommet*> m_voisins;

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position
};


#endif //PISCINE_SOMMET_H
