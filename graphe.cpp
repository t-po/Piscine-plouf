//
// Created by utilisateur on 15/04/2019.
//

#include <fstream>
#include <iostream>
#include "graphe.h"
#include "Svgfile.h"
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
    int id;
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
    int id_somDepart;
    int id_somArrive;
    //lecture des aretes
    for (int i=0; i<m_taille; ++i){
        //lecture des ids des deux extrémitées
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture id arete");
        ifs>>id_somDepart; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet Depart");
        ifs>>id_somArrive; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet Arrivee");

        m_aretes.insert({id,new arete{id,id_somDepart,id_somArrive}});
    }
    ifs.close();
    std::ifstream ifs2{nomFichierArete};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierGraphe );
    ifs2 >> m_taille;
    if ( ifs2.fail() )
        throw std::runtime_error("Problème lecture taille du graphe");
    int nb_ponde;
    float ponde;
    ifs2>>nb_ponde;
    for (int i=0; i<m_taille; ++i){
        ifs2>>id; if(ifs2.fail()) throw std::runtime_error("Probleme lecture id arete");
        for (int j=0;j<nb_ponde;j++){
            ifs2>>ponde; if(ifs2.fail()) throw std::runtime_error("Probleme lecture poids de l'arete");
            (m_aretes.find(id))->second->ajouterPonderation(ponde);
        }
    }

}

void graphe::afficher() const{                              ///Affiche le graphe
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"   ordre : " <<  m_ordre <<std::endl;
    for (auto it : m_sommets)
    {
        std::cout<<" Sommet : ";
        it.second->afficherData();
    }
    std::cout<<std::endl;
    std::cout<<"Il y a "<<m_taille<<" aretes"<<std::endl;
    for (auto ar:m_aretes)
    {
        std::cout<<" Aretes : ";
        ar.second->afficherAretes();
    }
}


void graphe::afficher_graphe(Svgfile& fic)
{
    double x1,x2,y1,y2,X,Y,X2,Y2;
    for ( auto  it = m_aretes.begin(); it != m_aretes.end(); ++it )
    {
        std::unordered_map<int,sommet*>::const_iterator got = m_sommets.find (it->second->getSomDepart());
        if ( got != m_sommets.end())
        {
            x1 = got->second->getX();
            y1 = got->second->getY();
        }

        got = m_sommets.find (it->second->getSomArrive());
        if ( got != m_sommets.end())
        {
            x2 = got->second->getX();
            y2 = got->second->getY();
        }
        fic.addLine(x1,y1,x2,y2,"black");
        X = (x1+x2)/2;
        Y = (y1+y2)/2 - 2;
        Y2 = Y;
        X2 = X;
        //for(auto p:it->second->getPond()) {
        if(y1 != y2 && x1 != x2)
        {
            if (x1<x2)
            {
                X2 = X;
                Y2= Y+15;
                X = X-15;
            }
            if(x1>x2)
            {
                X2 = X-10;
                Y2= Y+15;
                X = X+15;
            }

        }
        if(x1 == x2)
        {
            X2 = X+2;
            X = X-17;

        }
        if (y1 == y2)
        {
            X2 = X;
            Y2= Y+15;
        }

            std::vector<float> pond = it->second->getPond();
            fic.addText(X-7,Y,pond[0],"red");
            fic.addText(X,Y,":","black");
            fic.addText(X+7,Y,pond[1],"red");
            fic.addText(X2,Y2,it->second->getId());
        //}


    }
    for ( auto  it = m_sommets.begin(); it != m_sommets.end(); ++it )
    {
        fic.addDisk(it->second->getX(),it->second->getY(),10,"black");
        fic.addText(it->second->getX()-5,it->second->getY()+5,it->first,"white");

    }




}

std::vector <float> graphe::poid_total()
{
    float poid1 = 0;
    float poid2 = 0;
    std :: vector < float> poidTotal;


    for ( auto  it = m_aretes.begin(); it != m_aretes.end(); ++it )
    {
        std::vector<float> pond = it->second->getPond();
        poid1 = poid1 + pond[0];
        poid2 = poid2 + pond[1];

    }
    poidTotal[0] = poid1;
    poidTotal[1] = poid2;

    return poidTotal;

}


graphe::~graphe()
=default;
