//
// Created by utilisateur on 15/04/2019.
//

#ifndef PISCINE_ARETE_H
#define PISCINE_ARETE_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class vector;

class Arete {
    public:
        Arete(int, int mSomArrive, int mSomDepart);
        Arete();
        ~Arete();
        void ajouterPonderation(float);
        void afficherAretes()const;

        const std::vector<float> &getMPonderationVector() const;
        const float getMPonderation(int) const;
        int getMId();
        int getSomDepart (){return m_somDepart;};
        int getSomArrive (){return m_somArrive;};

    private:
        int m_id;
        int m_somDepart;
        int m_somArrive;
        std::vector<float> m_ponderation;



};


#endif //PISCINE_ARETE_H
