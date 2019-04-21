#include <iostream>
#include "graphe.h"
#include "Svgfile.h"


void pareto(std:: unordered_map<int,std::vector<float>> map_graphes);

int main() {
    Svgfile svgout;
    svgout.addGrid(100,true,"lightgrey");
    std::string id;
    graphe g{"../files/triville.txt","../files/triville_weights_0.txt"};
    g.afficher();///Affiche le graphe
    g.afficher_graphe(svgout);
    std::cout<<std::endl<<std::endl<<"PRIM"<<std::endl;
    graphe* g2=g.prim();
    g2->afficher();
    g2->afficher_graphe(svgout);
    std:: unordered_map<int,std::vector<float>> vect;
    std::cout<<"*************************"<<std::endl;
    std::vector<float>vv={18.0,14.0};
    vect.emplace(1,vv);
    vv={19.0,15.0};
    vect.emplace(2,vv);
    vv={13.0,15.0};
    vect.emplace(3,vv);
    vv={16.0,19.0};
    vect.emplace(4,vv);
    vv={17.0,20.0};
    vect.emplace(5,vv);
    vv={11.0,20.0};
    vect.emplace(6,vv);
    vv={22.0,18.0};
    vect.emplace(7,vv);
    vv={16.0,18.0};
    vect.emplace(8,vv);

    pareto(vect);

    return 0;
}


void pareto(std:: unordered_map<int,std::vector<float>> map_graphes)
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

    std::cout<<"************Parreto************ "<<std::endl;
for( auto  it = map_parreto.begin(); it != map_parreto.end(); ++it )
{
    std::cout<<"poid 1 : "<< it->second[0] << "      poid 2 : "<< it->second[1]<<std::endl;
}
}