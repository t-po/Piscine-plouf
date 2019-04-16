//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_ARETE_H
#define PISCINE_ARETE_H


#include "sommet.h"

class vector;

class arete {
    public:
        arete(int, int mSomArrive, int mSomDepart);
        ~arete();
        void ajouterPonderation(float);
        void afficherAretes()const;

        std::string getSomDepart (){return m_somDepart;};
        std::string getSomArrive (){return m_somArrive;};

    private:
        int m_id;
        int m_somDepart;
        int m_somArrive;
        std::vector<float> m_ponderation;

};


#endif //PISCINE_ARETE_H
