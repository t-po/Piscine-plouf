//
// Created by utilisateur on 15/04/2019.
//

#include "arete.h"

arete::arete(std::string id, std::string mSomArrive, std::string mSomDepart) : m_somArrive(mSomArrive), m_somDepart(mSomDepart), m_id(id) {
}

arete::~arete() {

}

void arete::ajouterPonderation(float ponde) {
    m_ponderation.push_back(ponde);
}



