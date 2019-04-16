//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_ARETE_H
#define PISCINE_ARETE_H


#include "sommet.h"

class vector;

class arete {
    public:
    arete();
    arete(int, int mSomArrive, int mSomDepart);
        ~arete();
        void ajouterPonderation(float);
        void afficherAretes()const;

        int getSomDepart (){return m_somDepart;};
        int getSomArrive (){return m_somArrive;};
        const float getMPonderation(int) const;

    private:
        int m_id;
        int m_somDepart;
        int m_somArrive;
        std::vector<float> m_ponderation;

};


#endif //PISCINE_ARETE_H
