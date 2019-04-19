#include <iostream>
#include "graphe.h"

int main() {
    std::string id;
    graphe g{"..//files//cubetown.txt","..//files//cubetown_weights_0.txt"};
    g.brute();



    return 0;
}