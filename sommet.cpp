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

sommet::sommet(std::string id,double x,double y):m_id{std::move(id)},m_x{x},m_y{y}
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