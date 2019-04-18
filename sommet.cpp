//
// Created by utilisateur on 15/04/2019.
//

#include <utility>

#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"
#include <set>
#include <list>

sommet::sommet(int id,double x,double y):m_id{std::move(id)},m_x{x},m_y{y}
{
}
void sommet::ajouterVoisin(const sommet* voisin){
    m_voisins.push_back(voisin);
}

void sommet::afficherData() const{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}
void sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins) {
        v->afficherData();
    }
}
int sommet::getDegre(){
    int degre=0;
    for(auto v:m_voisins) {
        degre++;
    }

    return degre;
}
sommet::~sommet()
{
    //dtor
}

void sommet::ajouterAretes( Arete * Arete) {
    m_aretePourSommet.push_back(Arete);
}

void sommet::trierAretes() {        ///Trie les aretes relié au sommet dans l'ordre croissant de la première pondérations.
    bool a=false;
    Arete* tmp;
    while(!a) {
        a=true;
        float poidsMax= m_aretePourSommet[0]->getMPonderation(0);
        for(int i=1;i<m_aretePourSommet.size();++i) {
            if (m_aretePourSommet[i]->getMPonderation(0) >= poidsMax) {
                poidsMax = m_aretePourSommet[i]->getMPonderation(0);
            } else {
                tmp = m_aretePourSommet[i];
                m_aretePourSommet[i] = m_aretePourSommet[i-1];
                m_aretePourSommet[i-1] = tmp;
                a = false;
            }
        }
    }
}

std::vector< Arete *> sommet::getMAretePourSommet()  {
    return m_aretePourSommet;
}

int sommet::getMId()  {
    return m_id;
}

void sommet::afficherAretePourSommet() {
    for(auto ar:m_aretePourSommet){
        std::cout<<ar->getMPonderation(0)<<std::endl;
    }
}
