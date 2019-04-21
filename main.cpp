#include <iostream>
#include "graphe.h"
#include "Svgfile.h"


void pareto(std:: unordered_map<int,std::vector<float>> map_graphes);

int main() {
    Svgfile svgout;
    svgout.addGrid(100,true,"lightgrey");
    std::string id;
    graphe g{"../files/cubetown.txt","../files/cubetown_weights_0.txt"};
    g.afficher();///Affiche le graphe
    g.afficher_graphe(svgout);
    std::cout<<std::endl<<std::endl<<"PRIM"<<std::endl;
    graphe* g2=g.prim();
    g2->afficher();
    g2->afficher_graphe(svgout);
    g.brute();



    return 0;
}


void pareto(std:: unordered_map<int,std::vector<float>> map_graphes)
{

    std::unordered_map<int, std::vector<float >> map_parreto;
    //std::vector<std::vector<float>>tri;
    float Xmemoire = map_graphes.begin()->second[0];
    float Ymemoire = map_graphes.begin()->second[1];
    int compteur = 0;
    int id_graphe;
    float Ymax;
    bool effacer = false;
    std::cout<<"0"<<std::endl;
    do {

        Xmemoire = map_graphes.begin()->second[0];
        Ymemoire = map_graphes.begin()->second[1];
        for ( auto  it = map_graphes.begin(); it != map_graphes.end(); ++it )
        {

            std::cout<< it->second[0] << "comparer a " << Xmemoire <<std::endl;
            if (it->second[0] < Xmemoire)
            {
            std::cout<<it->second[0]<< "est rentrer dans la boucle" <<std::endl;
                Xmemoire = it->second[0];
                Ymemoire = it->second[1];
                id_graphe = it->first;

            }
            else if (it->second[1] > Ymemoire)
            {

                effacer = true;
                //map_graphes.erase(it);
                //it--;

            }

            if (it->second[0] == Xmemoire && it->second[1]<= Ymemoire)
            {
                Xmemoire = it->second[0];
                Ymemoire = it->second[1];
                id_graphe = it->first;
            }

            if(effacer == true)
            {
                auto it2 = it--;
                std :: cout<<it2->second[0]<< " a ete effacer"<<std::endl;
                map_graphes.erase(it2);
                effacer = false;
            }
        }

        if (compteur == 0)
        {
            Ymax = Ymemoire;
            compteur++;
        }
        if (Ymemoire <= Ymax)
        {

            compteur++;
            std::vector<float> tampon;
            tampon.push_back(Xmemoire);
            tampon.push_back(Ymemoire);
            Ymax = Ymemoire;
            std::cout<<"***poid final  : 1 : "<<Xmemoire<<"    poid  final 2 :  "<< Ymemoire<<std::endl;
            map_parreto.insert({id_graphe, tampon});
            map_graphes.erase(id_graphe);

        }



    } while (map_graphes.size() > 0);

    std::cout<<"************Parreto************ "<<std::endl;
for( auto  it = map_parreto.begin(); it != map_parreto.end(); ++it )
{
    std::cout<<"poid 1 : "<< it->second[0] << "      poid 2 : "<< it->second[1]<<std::endl;
}
}