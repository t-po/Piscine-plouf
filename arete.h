//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_ARETE_H
#define PISCINE_ARETE_H


#include "sommet.h"

class vector;

class arete {
    public:
        arete(int, std::string mSomArrive, std::string mSomDepart);
        ~arete();
        void ajouterPonderation(float);
        void afficherAretes()const;

    private:
        int m_id;
        std::string m_somDepart;
        std::string m_somArrive;
        std::vector<float> m_ponderation;

};


#endif //PISCINE_ARETE_H
