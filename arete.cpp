//
// Created by utilisateur on 15/04/2019.
//

#include <iostream>
#include "arete.h"
#include <vector>

arete::arete(int id, int mSomArrive, int mSomDepart) : m_somArrive(mSomArrive), m_somDepart(mSomDepart), m_id(id) {
}

arete::arete() {

}

arete::~arete() {

}

void arete::ajouterPonderation(float ponde) {
    m_ponderation.push_back(ponde);
}

void arete::afficherAretes() const{
    std::cout<<"  id :"<< m_id <<std::endl;
    std::cout<<"Poids : ";
    for(auto p:m_ponderation) {
        std::cout<<p<<"   ";
    }
    std::cout<<std::endl;
    std::cout<<"Sommet de depart : " <<m_somDepart <<std::endl;
    std::cout<<"Sommet d'arrive :" <<m_somArrive <<std::endl;
}



const float arete::getMPonderation(int id) const {
    return m_ponderation[id];
}



