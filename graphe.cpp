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

void graphe::voisin(int Sommet) {
   /* for (int i = 0; i < m_aretes.size(); i++)
        if ((Sommet == m_aretes.find(i)->second->getSomArrive()) ||
            (Sommet == m_aretes.find(i)->second->getSomDepart())) {
            std::cout << Sommet;
        }*/
}


void graphe::kruskal() ///Prim
{
    std::unordered_map<int,arete*> arbre;
    int indice1=0;
    std::vector <int> marques;
    int Sommet;
    int x,y,ymin;
    float min;

    Sommet=rand()%m_ordre;
    Sommet='0';
    marques[Sommet]=1;

    while (indice1<m_ordre-1)
    {
        min=INFINITY;
        for (x=0;x<m_ordre;x++)
            if(marques[x])
                for (y=0;y<m_ordre;y++)
                    std::cout <<" ";
                voisin (Sommet);

    }
    std::cout <<m_taille << std::endl;
}

graphe::~graphe()
=default;
