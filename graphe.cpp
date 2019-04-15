//
// Created by utilisateur on 15/04/2019.
//

#include <fstream>
#include <iostream>
#include "graphe.h"
#include <unordered_map>
#include <unordered_set>
#include <set>

graphe::graphe(std::string nomFichierGraphe, std::string nomFichierArete) {
    std::ifstream ifs{nomFichierGraphe};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierGraphe );
    ifs >> m_ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Problème lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<m_ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Problème lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Problème lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Problème lecture données sommet");
        m_sommets.insert({id,new sommet{id,x,y}});
    }
    ifs >> m_taille;
    if ( ifs.fail() )
        throw std::runtime_error("Problème lecture taille du graphe");
    std::string id_somDepart;
    std::string id_somArrive;
    //lecture des aretes
    for (int i=0; i<m_taille; ++i){
        //lecture des ids des deux extrémitées
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_somDepart; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_aretes.find(id))->second->m_somDepart;
        (m_sommets.find(id_somDepart))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
    }
}

void graphe::afficher() const{                              ///Affiche le graphe
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"   ordre : " <<  m_ordre <<std::endl;
    for (auto it : m_sommets)
    {
        std::cout<<" Sommet : ";
        it.second->afficherData();
        it.second->afficherVoisins();
        std::cout<<"  Degre:"<< it.second->getDegre()<<std::endl;
    }
}

graphe::~graphe()
=default;
