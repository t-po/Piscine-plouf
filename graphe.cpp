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

bool * graphe::decToBinary(int n)
{

    bool *binNum = new bool [32];

    for(size_t i=0;i<32;i++)
        binNum[i]=0;


    int i = 0;
    while (n > 0) {
        binNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    //std::cout<<"test : ";


        return  binNum;
}



std::unordered_map< int,std::vector<float> > graphe::brute()
{

    int cmpAretes=0;
    int filtre2;
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
        if (filtre2==1)
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
    std::unordered_map<int,arete*> aretesStockes;   /// Toutes les aretes sont stockés dedans
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
            return 0;
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
            return 0;
    }

    /// Sinon il est connexe
    return 1;
}

std::vector<float> graphe::poidsDuGraphe (std::vector <bool> b2)
{
    std::vector <float> stockPoids;
    std::unordered_map<int,arete*> aretesStockes;   /// Toutes les aretes sont stockés dedans
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
    for (size_t j=0;j<aretesStockes.find(j)->second->getMPonderation()[j];j++)
    {
        stockPoids.push_back(0);
    }

    ///On incrémente la valeur de chaque dimension dans stockPoids
    for (size_t i=0;i<aretesStockes.size();i++)
    {
        for (size_t j=0;j<aretesStockes.find(i)->second->getMPonderation().size();j++)
        {
            stockPoids[j]=stockPoids[j]+ aretesStockes.find(i)->second->getMPonderation()[j];
        }
    }

    /// On retourne le poid de chaque dimension
    return stockPoids;
}

graphe::~graphe()
=default;
