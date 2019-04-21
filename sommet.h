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
#include "Arete.h"


class sommet {
    public:
        ///constructeur qui reçoit en params les données du sommet
        sommet(int,double,double);
        ~sommet();
        void ajouterVoisin(const sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        int getDegre();
        void ajouterAretes( Arete*);
        void trierAretes();     ///Trie les aretes relié au sommet dans l'ordre croissant de la première pondérations.
        std::vector< Arete *> getMAretePourSommet() ;
        int getMId() ;
        void afficherAretePourSommet();
        double getX();
        double getY();
        float getPoidsSubjectif() const;
        void setPoidsSubjectif(float poidsSubjectif);

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const sommet*> m_voisins;
        std::vector< Arete*> m_aretePourSommet;


        /// Données spécifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position
        float poidsSubjectif;    ///SPECIAL DIJKSTRA
};


#endif //PISCINE_SOMMET_H
