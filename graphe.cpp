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

bool * graphe::decToBinary(int n)
{
    bool *binNum = new bool [32];
    for(size_t i=0;i<32;i++)
        binNum[i]=false;
    int i = 0;
    while (n > 0) {
        binNum[i] = n % 2;
        n = n / 2;
        i++;
    }
        return  binNum;
}

std::unordered_map< int,std::vector<float> > graphe::brute()
{

    int cmpAretes=0;
    bool filtre2;
    int nbCasPossibles= pow(2,m_taille);    /// Enumaration des cas possibles
    std::vector<std::vector<bool> > solAdmissible;
    std::vector<std::vector<bool> > solVraimentAdmissible;
    std::vector<bool> b2;
    std::unordered_map< int,std::vector<float> > poidDimensionsGraphe;

    for (int j=0;j<nbCasPossibles;j++)  /// Réalisation des différents cas
    {
        bool *binNum = decToBinary(j);
        std::vector <bool> b1;

        for (int k = 0;k<m_taille;k++)  ///On rogne le tableau pour qu'il corresponde à la dimension du graphe choisi
        {
            b1.push_back(binNum[k]);
        }

        for (size_t i = 0; i < b1.size(); ++i) {
            if (b1[i]==1)
                cmpAretes++;
        }

        /// Premier tri
        if (cmpAretes==(m_ordre-1))
            solAdmissible.push_back(b1);

        /// On reinitialise les valeurs
        b1.erase(b1.begin(),b1.end());
        cmpAretes=0;
    }

    /// Deuxième tri
   for (size_t i = 0; i<solAdmissible.size(); i++)
    {
       filtre2=connexite(solAdmissible[i]);

       /// Si la connexité est positive, on ajoute le vecteur à un nouveau vecteur de solutions
        if (filtre2)
        {
            solVraimentAdmissible.push_back(solAdmissible[i]);
        }
    }

    /// On récupère le poid de toutes les dimensions de chaque graphe
    for (size_t i = 0; i<solVraimentAdmissible.size(); i++)
    {
        poidDimensionsGraphe.insert({i,poidsDuGraphe(solVraimentAdmissible[i])});
    }

   ///On affiche toutes les solutions, leurs dimensions et le poid de chaque dimension
    for (int i = 0;i<solVraimentAdmissible.size();i++)
    {
        for (int j = m_taille-1; j >= 0; j--)
        {
            std::cout << solVraimentAdmissible[i][j];

        }
        std::cout << std::endl<<poidDimensionsGraphe.find(i)->first<< " x = "
                  << poidDimensionsGraphe.find(i)->second[0]<< " y = "
                  <<poidDimensionsGraphe.find(i)->second[1]<<std::endl<< std::endl;

    }

    /// Affichage du nombre de solutions Admissibles
    std::cout << solVraimentAdmissible.size() <<'\n';

return poidDimensionsGraphe;
}

bool graphe::connexite(std::vector <bool> b2)
{

    std::unordered_map<int,int> connexiteDuSommet; /// La connexité de chaque sommet
    std::unordered_map<int,Arete*> aretesStockes;   /// Toutes les aretes sont stockés dedans
    int id=0;
    int temp;

    /// On initialise la connexité de chaque sommet a la meme valeure que son id
    for (int i=0;i<m_ordre;i++)
    {
        connexiteDuSommet.insert({i,i});
    }


    for (int i= 0; i< b2.size();i++)
    {
        ///On insère les aretes qui existent dans un nouveau vecteur d'aretes
        if (b2[i]==1)
        {
            aretesStockes.insert( {id, m_aretes.find(i)->second});
            id++;   /// id augmente a chaque fois, ainsi on a des valeurs pour 0,1,2,... au lieu d'avoir 1,3,4,...
        }
    }

    /// Pour toutes les aretes, on vérifie la connexité
    for (size_t j=0;j<aretesStockes.size();j++)
    {

        ///Si deux Sommets on la meme composante connexe, alors on crée un cycle, donc ce n'est pas connexe
        /// (pas vraiment utile en fait)
       if(connexiteDuSommet.find(aretesStockes.find(j)->second->getSomArrive())->second
       == connexiteDuSommet.find(aretesStockes.find(j)->second->getSomDepart())->second)
        {
            return false;
        }

       /// Deux sommets reliés par une arete ont une composante connexe différente,
       /// On veux qu'ils aient la même et que leurs prédécesseurs aussi
       /// Pour ça, on stock la valeur de l'un dans temp
       temp =connexiteDuSommet.find(aretesStockes.find(j)->second->getSomDepart())->second;

       /// Les deux prennent la même valeure
       connexiteDuSommet.find(aretesStockes.find(j)->second->getSomDepart())->second
       = connexiteDuSommet.find(aretesStockes.find(j)->second->getSomArrive())->second;

       /// Puis tous les sommets avec la même composante que l'ancien prennent la nouvelle valeure
            for (size_t i=0;i<connexiteDuSommet.size();i++)
            {
                if(connexiteDuSommet.find(i)->second==temp)
                {
                    connexiteDuSommet.find(i)->second
                    =connexiteDuSommet.find(aretesStockes.find(j)->second->getSomArrive())->second;
                }
            }
    }

    /// Si deux Sommets ont une connexité différente, le graphe n'est pas connexe
    for(size_t i=1;i<connexiteDuSommet.size(); i++)
    {
        if(connexiteDuSommet.find(i-1)->second!=connexiteDuSommet.find(i)->second)
            return false;
    }

    /// Sinon il est connexe
    return true;
}

std::vector<float> graphe::poidsDuGraphe (std::vector <bool> b2)
{
    std::vector <float> stockPoids;
    std::unordered_map<int,Arete*> aretesStockes;   /// Toutes les aretes sont stockés dedans
    int id=0;

    for (int i= 0; i< b2.size();i++)
    {
        ///On insère les aretes qui existent dans un nouveau vecteur d'aretes
        if (b2[i]==1)
        {
            aretesStockes.insert( {id, m_aretes.find(i)->second});
            id++;   /// id augmente a chaque fois, ainsi on a des valeurs pour 0,1,2,... au lieu d'avoir 1,3,4,...
        }
    }

    ///Initialisation pour chaque dimension à 0
    for (size_t j=0;j<aretesStockes.find(j)->second->getMPonderationVector()[j];j++)
    {
        stockPoids.push_back(0);
    }

    ///On incrémente la valeur de chaque dimension dans stockPoids
    for (size_t i=0;i<aretesStockes.size();i++)
    {
        for (size_t j=0;j<aretesStockes.find(i)->second->getMPonderationVector().size();j++)
        {
            stockPoids[j]=stockPoids[j]+ aretesStockes.find(i)->second->getMPonderationVector()[j];
        }
    }

    /// On retourne le poid de chaque dimension
    return stockPoids;
}


void graphe::pareto(std:: unordered_map<int,std::vector<float>> map_graphes)
{

    std::unordered_map<int, std::vector<float >> map_parreto;
    //std::vector<std::vector<float>>tri;
    /// on crée trois variables pour enregister les points de la frontieres de pareto avec les poid et l'id
    float Xmemoire = map_graphes.begin()->second[0];
    float Ymemoire = map_graphes.begin()->second[1];
    int id_graphe;

    int id_graphe_effacer;
    bool effacer = false;
    int compteur = 0;
    float Ymax;/// cette variable nous servira pour apres avoir trier le poid 1
    bool vide = true;
    ///notre but va être de trouver touts les solutions de pareto en parcourant le poid 1
    do {

        Xmemoire = map_graphes.begin()->second[0];/// on recommence au debut de la map
        Ymemoire = map_graphes.begin()->second[1];
        for ( auto  it = map_graphes.begin(); it != map_graphes.end(); ++it ) /// pour toutes les valeurs données par le brut force
        {


            if(effacer == true) ///on efface ce qui avait au tour d'avant pour eviter de fzire planter le code
            {
                map_graphes.erase(id_graphe_effacer);
                effacer = false;
            }
            if (it->second[0] < Xmemoire) /// si le poid 1 est inférieur à celui en memoire
            {
                /// c'est le sommet avec le plus petit poid à ce rang
                Xmemoire = it->second[0];
                Ymemoire = it->second[1];
                id_graphe = it->first;

            }
            else if (it->second[1] > Ymemoire) /// si les poids 1 et 2 sont supérieur alor ce ne sera dans tous les cas pas une solution de pareto on peut donc allger la liste
            {
                id_graphe_effacer = it->first;
                effacer = true;

            }

            if (it->second[0] == Xmemoire && it->second[1]<= Ymemoire)/// dans le cas de deux poid 1 egaux alor on prend celui avec le poid 2 le plus petit
            {
                Xmemoire = it->second[0];
                Ymemoire = it->second[1];
                id_graphe = it->first;
            }

        }

        if (vide == true )/// si notre liste de fin comptant toutes les solutions de parreto esy vide
        {
            Ymax = Ymemoire;//
            vide = false;
        }
        if (Ymemoire <= Ymax)/// si l'on range dans l'odre croissaznt les solutions on peut voir que si le poid 1 augmente le poid 2 diminue donc si le poid 2 est inferieur au poid  2 précédent alor c'est une solution
        {

            std::vector<float> tampon;
            tampon.push_back(Xmemoire);
            tampon.push_back(Ymemoire);
            Ymax = Ymemoire; /// on sauvegarde le dernier poid 2
            map_parreto.insert({id_graphe, tampon});
            map_graphes.erase(id_graphe); /// on peut donc supprimmer ce point

        }



    } while (map_graphes.size() > 0);

    std::cout<<"***********Parreto*********** "<<std::endl;
    for( auto  it = map_parreto.begin(); it != map_parreto.end(); ++it )
    {
        std::cout<<"poid 1 : "<< it->second[0] << "      poid 2 : "<< it->second[1]<<std::endl;
    }
}

graphe::~graphe()
=default;
