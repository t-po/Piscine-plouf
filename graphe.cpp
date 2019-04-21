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
    std::cout<<"ici"<<std::endl;
    trierAretesPourToutSommet(0);  ///Pour chaque sommet : trie le vecteur d'aretes relié au sommet
    std::cout<<"la"<<std::endl;
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
    listAretesSommet.push_back(m_sommets.find(0)->second->getMAretePourSommet());            ///J'incrémente listAreteSommet
    while (nouveauxSommets.size()<m_sommets.size()){                                  ///Pour chaque sommet
        if (listAretesSommet.size()>1) {
            for (unsigned int i = 0; i < listAretesSommet.size(); ++i) {                       ///Recherche du poid minimal
                if (listAretesSommet[i][0]->getMPonderation(0) < poidMin) {
                    poidMin = listAretesSommet[i][0]->getMPonderation(0);
                    id = i;
                }
            }
        }
        isPresentDep = estPresentMap((listAretesSommet[id][0])->getSomDepart(),
                                     nouveauxSommets); ///le sommet de départ est-il déjà découvert
        isPresentArr = estPresentMap(listAretesSommet[id][0]->getSomArrive(),
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
        listAretesSommet[id].erase(listAretesSommet[id].begin());   ///Suppression de l'arete selectionné
        if (listAretesSommet[id].empty()){          ///Si toutes les aretes d'un sommet ont été utilisé, on supprime le vecteur d'arete.
            listAretesSommet.erase(listAretesSommet.begin()+id);}
        poidMin=listAretesSommet[id][0]->getMPonderation(0); ///prend le premier poids de la premiere arete du vecteur de vecteur
    }
    graphe* g=new graphe(nouvellesAretes.size(), nouveauxSommets.size(), nouveauxSommets,nouvellesAretes);
    return (g);
}

void graphe::trierAretesPourToutSommet(int id) {
    for (auto so:m_sommets){            ///Pour chaque sommet : trie le vecteur d'aretes relié au sommet
        so.second->trierAretes(id);
    }
}

bool graphe::estPresentMap( int id, std::unordered_map<int, sommet *> table) {
    for(auto it:table){
        if(it.second->getMId() == id){
            return true;
        }
    }
    return false;
}

bool graphe::estPresentVector(int id, std::vector<Arete *>vect) {
    for(auto it:vect){
        if(it->getMId()==id){
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

sommet* graphe::sommetSuivant(sommet* sommetActuel, Arete* areteActuelle){
    if( m_sommets.find(areteActuelle->getSomDepart())->second!=sommetActuel){
        return m_sommets.find(areteActuelle->getSomDepart())->second;
    }
    else{
        return m_sommets.find(areteActuelle->getSomArrive())->second;
    }
}



/*
float graphe::dijkstra(int i) {
    std::vector<int>sommetsPris;
    float sommePoidsMin=0;
    int max=m_ordre;

    trierAretesPourToutSommet(1);

    while(sommetsPris.size() <= m_ordre) {
        Arete* areteActuelle=m_sommets.find(i)->second->getMAretePourSommet()[0];
        sommet* sommetActuel=m_sommets.find(i)->second;
        std::vector<Arete*> listAretesPrecedantes;        ///Vecteur de vecteur d'aretes. Pour trouver la branche de poids minimum.
        std::vector<sommet*> sommetsPrecedants;


        sommetActuel->setPoidsSubjectif(0);
        float poidsMin=areteActuelle->getMPonderation(1);
        int id=-1;

        while (sommetActuel!=m_sommets.find(max-1)->second){

            sommetsPrecedants.push_back(sommetActuel);
            sommetActuel=sommetSuivant(sommetActuel,areteActuelle);
            listAretesPrecedantes.push_back(areteActuelle);

            if (sommetActuel->getPoidsSubjectif() > poidsMin){
                sommetActuel->setPoidsSubjectif(poidsMin);
            }


            ///Trouve la meilleure voie
            int j = 0;
            for (int k = 0; k < sommetActuel->getMAretePourSommet().size(); ++k) {
                if (estPresentVector(sommetActuel->getMAretePourSommet()[j]->getMId(), listAretesPrecedantes)) {
                    j++;
                }
            }
            if (j == sommetActuel->getMAretePourSommet().size()-1){
                continue;
            }
            float testPoidsMin=sommetActuel->getMAretePourSommet()[j]->getMPonderation(1) + sommetActuel->getPoidsSubjectif();    ///Déclaration et set de testPoidsMin
            Arete* testMeilleureArete=sommetActuel->getMAretePourSommet()[j];
            int m=0;
            for (unsigned int l = 0; l < sommetsPrecedants.size(); ++l) {    ///Recherche du poid minimal

                ///Selection d'une arete qu'on a pas encore utilisé
                for (int k = 0; k < sommetsPrecedants[l]->getMAretePourSommet().size(); ++k) {
                    if (estPresentVector(sommetsPrecedants[l]->getMAretePourSommet()[m]->getMId(),listAretesPrecedantes)) {
                        m++;
                    }
                }///
                if (m == sommetsPrecedants[l]->getMAretePourSommet().size()-1){
                    continue;
                }
                ///Choix de la meilleure arete
                if (sommetsPrecedants[l]->getMAretePourSommet()[m]->getMPonderation(1) + sommetsPrecedants[l]->getPoidsSubjectif() < testPoidsMin) {
                    testPoidsMin = sommetsPrecedants[l]->getMAretePourSommet()[m]->getMPonderation(1);
                    id = l;
                    testMeilleureArete=sommetsPrecedants[l]->getMAretePourSommet()[m];
                }///
            }
            ///
            if(id == -1){
                poidsMin+=sommetActuel->getPoidsSubjectif();
                areteActuelle=testMeilleureArete;
            }
            else{
                poidsMin+=sommetsPrecedants[id]->getPoidsSubjectif();
                areteActuelle=testMeilleureArete;
            }
            //std::cout<<"Le poids du sommet "<<sommetActuel->getMId()<<" est : "<<sommetActuel->getPoidsSubjectif()<<std::endl;
            std::cout<<"SommetsPris : ";
            for(auto so:sommetsPris){
                std::cout<<so<<";";
            }
            std::cout<<std::endl;
            std::cout<<"Sommet Actuel : "<<areteActuelle->getMId()<<std::endl;
            std::cout<<"Sommets Precedents : ";
            for(auto so:sommetsPrecedants){
                std::cout<<so->getMId()<<";";
            }
            std::cout<<std::endl;
            std::cout<<"Arete Actuelle : "<<areteActuelle->getMId()<<std::endl;
            std::cout<<"Aretes Precedentes : ";
            for(auto ar:listAretesPrecedantes){
                std::cout<<ar->getMId()<<";";
            }
            std::cout<<std::endl;
        }
        //std::cout<<"Le poids du sommet "<<max-1<<" est : "<<sommetActuel->getPoidsSubjectif()<<std::endl;
        sommetsPris.push_back(areteActuelle->getMId());
        sommePoidsMin+=poidsMin;
        std::cout<<"Pour aller au sommet "<<max-1<<" le poids min est de : "<<poidsMin<<std::endl;
        max--;
    }
    return sommePoidsMin;
}

float graphe::calculPr2() {
    float Pr2=0;
    *//*for (int i = 0; i < m_sommets.size(); ++i) {
        Pr2+=dijkstra(i);
    }*//*
    Pr2=dijkstra(0);
    ///somme des Dijkstras.
    return Pr2;
}*/

const std::unordered_map<int, sommet *> &graphe::getMSommets() const {
    return m_sommets;
}



float graphe::TrouvePoidsEntreDeuxSommets(sommet* sommet1,sommet* sommet2){

    for(auto arete:m_aretes){
        if(arete.second->getSomArrive()==sommet1->getMId() || arete.second->getSomArrive()==sommet1->getMId()){
            if(sommet2 == sommetSuivant(sommet1,arete.second)) {
                return arete.second->getMPonderation(1);
            }
        }
    }
}

/*std::vector <float> graphe::poid_total()
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

}*/


graphe::~graphe()
=default;
