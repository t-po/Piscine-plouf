//
// Created by utilisateur on 15/04/2019.
//

#include <iostream>
#include "Arete.h"
#include <vector>

Arete::Arete(int id, int mSomArrive, int mSomDepart) : m_somArrive(mSomArrive), m_somDepart(mSomDepart), m_id(id) {
}

Arete::Arete() {

}

Arete::~Arete() {

}

void Arete::ajouterPonderation(float ponde) {
    m_ponderation.push_back(ponde);
}

void Arete::afficherAretes() const{
    std::cout<<"  id :"<< m_id <<std::endl;
    std::cout<<"Poids : ";
    for(auto p:m_ponderation) {
        std::cout<<p<<"   ";
    }
    std::cout<<std::endl;
    std::cout<<"Sommet de depart : " <<m_somDepart <<std::endl;
    std::cout<<"Sommet d'arrive :" <<m_somArrive <<std::endl;
}

const std::vector<float> &Arete::getMPonderationVector() const {
    return m_ponderation;
}



const float Arete::getMPonderation(int id) const {
    return m_ponderation[id];
}

int Arete::getMId()  {
    return m_id;
}





