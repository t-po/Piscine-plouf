//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_ARETE_H
#define PISCINE_ARETE_H


#include "sommet.h"

class vector;

class arete {
    public:
        arete(int , int , int,std::vector<float>);

    private:
        int m_id;
        int m_somDepart;
        int m_somArrive;
        std::vector<float> m_ponderation;

};


#endif //PISCINE_ARETE_H
