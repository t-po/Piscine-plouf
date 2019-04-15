//
// Created by utilisateur on 15/04/2019.
//

#include "arete.h"

arete::arete(sommet mSomArrive, sommet mSomDepart) : m_somArrive(mSomArrive), m_somDepart(mSomDepart) {
}

arete::~arete() {

}

void arete::ajouterDepart(sommet Depart) {
    m_somDepart=Depart;
}

void arete::ajouterArrivee(sommet Arrivee) {
    m_somArrive=Arrivee;
}


