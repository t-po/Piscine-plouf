#include <utility>

#include <utility>

//
// Created by utilisateur on 15/04/2019.
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "graphe.h"
#include "Svgfile.h"

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
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture id Arete");
        ifs>>id_somDepart; if(ifs.fail()) throw std::runtime_error("Probleme lecture Arete sommet Depart");
        ifs>>id_somArrive; if(ifs.fail()) throw std::runtime_error("Probleme lecture Arete sommet Arrivee");
        auto* actualArete= new Arete{id,id_somDepart,id_somArrive};
        m_sommets.find(id_somDepart)->second->ajouterAretes(actualArete); ///Ajoute l'Arete au vecteur des aretes relié au sommet
        m_sommets.find(id_somArrive)->second->ajouterAretes(actualArete); ///Ajoute l'Arete au vecteur des aretes relié au sommet
        m_aretes.insert({id,actualArete});
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
        ifs2>>id; if(ifs2.fail()) throw std::runtime_error("Probleme lecture id Arete");
        for (int j=0;j<nb_ponde;j++){
            ifs2>>ponde; if(ifs2.fail()) throw std::runtime_error("Probleme lecture poids de l'Arete");
            (m_aretes.find(id))->second->ajouterPonderation(ponde);
        }
    }
    trierAretesPourToutSommet();  ///Pour chaque sommet : trie le vecteur d'aretes relié au sommet
}

graphe::graphe(int mtaille, int mordre, std::unordered_map<int, sommet *> msommets, std::unordered_map<int, Arete *> maretes) : m_taille(mtaille), m_ordre(mordre), m_sommets(msommets), m_aretes(maretes) {

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

graphe* graphe::prim() {
    ///Décalarations des variables
    std::unordered_map<int, sommet*> nouveauxSommets;               ///unordored map de sommet du graphe donner par Prim
    std::unordered_map<int, Arete*> nouvellesAretes;           ///unordored map d'aretes du graphe donner par Prim
    std::vector<std::vector< Arete*>> listAretesSommet;        ///Vecteur de vecteur d'aretes. Pour trouver la branche de poids minimum.
    bool isPresentDep;                  ///Variable pour savoir si le sommet de départ est déjà découvert
    bool isPresentArr;                  ///Variable pour savoir si le sommet de d'arrivé est déjà découvert
    float poidMin=(m_sommets.find(0)->second->getMAretePourSommet())[0]->getMPonderation(0); ///prendra le plus petit poids de listAretesSommet
    int id=0;                           ///id de l'arete de plus petit poids.

    nouveauxSommets.insert({m_sommets.find(0)->second->getMId(),m_sommets.find(0)->second}); ///Sommet0 insérer dans la nouvelle unordored map
    listAretesSommet.push_back(m_sommets.find(0)->second->getMAretePourSommet());
    while (nouveauxSommets.size()<m_sommets.size()){                                  ///Pour chaque sommet
        if (listAretesSommet.size()>1) {
            for (unsigned int i = 0; i < listAretesSommet.size(); ++i) {                       ///Recherche du poid minimal
                if (listAretesSommet[i][0]->getMPonderation(0) < poidMin) {
                    poidMin = listAretesSommet[i][0]->getMPonderation(0);
                    id = i;
                }
            }
        }
        isPresentDep = estPresent((listAretesSommet[id][0])->getSomDepart(),
                                  nouveauxSommets); ///le sommet de départ est-il déjà découvert
        isPresentArr = estPresent(listAretesSommet[id][0]->getSomArrive(),
                                  nouveauxSommets);   ///le sommet de d'arrivé est-il déjà découvert
        if (!isPresentDep || !isPresentArr) {                                                ///Si un des deux n'est pas découvert
            nouvellesAretes.insert(
                    {listAretesSommet[id][0]->getMId(), listAretesSommet[id][0]});    ///On enregistre l'arete
            if (!isPresentArr) {                                                              ///Si c'est le sommet d'arrivé qui n'est pas parcourue
                nouveauxSommets.insert({listAretesSommet[id][0]->getSomArrive(),
                                        m_sommets.find(listAretesSommet[id][0]->getSomArrive())->second});  ///on l'insère dans le tableau pour qu'il le soit
                listAretesSommet.push_back(m_sommets.find(listAretesSommet[id][0]->getSomArrive())->second->getMAretePourSommet());///met son vecteur d'arete dans listAretesSommet
            }
            else {                                                                            ///Si c'est le sommet de départ qui n'est pas parcourue
                nouveauxSommets.insert({listAretesSommet[id][0]->getSomDepart(),
                                        m_sommets.find(listAretesSommet[id][0]->getSomDepart())->second});   ///on l'insère dans le tableau pour qu'il le soit
                listAretesSommet.push_back(m_sommets.find(listAretesSommet[id][0]->getSomDepart())->second->getMAretePourSommet());///met son vecteur d'arete dans listAretesSommet
            }

        }
        listAretesSommet[id].erase(listAretesSommet[id].begin());
        if (listAretesSommet[id].empty()){
            listAretesSommet.erase(listAretesSommet.begin()+id);}
        poidMin=listAretesSommet[id][0]->getMPonderation(0); ///prend le premier poids de la premiere arete du vecteur de vecteur
    }
    graphe* g=new graphe(nouvellesAretes.size(), nouveauxSommets.size(), nouveauxSommets,nouvellesAretes);
    return (g);
}

void graphe::trierAretesPourToutSommet() {
    for (auto so:m_sommets){            ///Pour chaque sommet : trie le vecteur d'aretes relié au sommet
        so.second->trierAretes();
    }
}

bool graphe::estPresent( int id, std::unordered_map<int, sommet *> table) {
    for(auto it:table){
        if(it.second->getMId() == id){
            return true;
        }
    }
    return false;
}

void graphe::afficherAretePourToutSommet() {
    for(auto so:m_sommets){
        so.second->afficherAretePourSommet();
        std::cout<<"ici"<<std::endl;
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

            fic.addText(X-7,Y,it->second->getMPonderation(0),"red");
            fic.addText(X,Y,":","black");
            fic.addText(X+7,Y,it->second->getMPonderation(1),"red");
            fic.addText(X2,Y2,it->second->getMId());
        //}


    }
    for ( auto  it = m_sommets.begin(); it != m_sommets.end(); ++it )
    {
        fic.addDisk(it->second->getX(),it->second->getY(),10,"black");
        fic.addText(it->second->getX()-5,it->second->getY()+5,it->first,"white");

    }




}



graphe::~graphe()
=default;
