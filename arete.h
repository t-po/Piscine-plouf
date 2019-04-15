//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_ARETE_H
#define PISCINE_ARETE_H


#include "sommet.h"

class vector;

class arete {
    public:
        arete(std::string, std::string mSomArrive, std::string mSomDepart);
        ~arete();
        void ajouterPonderation(float);

    private:
        std::string m_id;
        std::string m_somDepart;
        std::string m_somArrive;
        std::vector<float> m_ponderation;

};


#endif //PISCINE_ARETE_H
