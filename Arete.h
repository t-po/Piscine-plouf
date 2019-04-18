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






class Arete {
    public:
        Arete();
        Arete(int, int mSomArrive, int mSomDepart);
        ~Arete();
        void ajouterPonderation(float);
        void afficherAretes()const;

        int getSomDepart () const {return m_somDepart;};
        int getSomArrive () const {return m_somArrive;};
        const float getMPonderation(int) const;
        int getMId();


    private:
        int m_id;

        int m_somDepart;
        int m_somArrive;
        std::vector<float> m_ponderation;



};


#endif //PISCINE_ARETE_H
