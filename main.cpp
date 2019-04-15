#include <iostream>
#include "graphe.h"

int main()
{
    graphe g{"cubetown.txt","cubetown_weights_0.txt"};
    g.afficher();
    g.afficherBFS("1");
    g.afficherDFS("1");
    int ncc=g.rechercher_afficherToutesCC();
    std::cout<<"Nombre de composantes connexes: "<<ncc<<std::endl;
    std::cout<<"le graphe est-il eulerien ?"<<std::endl<<std::endl;
    int resultat=g.isEulerien();
    if (resultat == 0)
        std::cout<<"Le graphe n'est pas eulerien."<<std::endl;
    if (resultat == 1)
        std::cout<<"Le graphe admet une chaine eulerien."<<std::endl;
    if (resultat == 2)
        std::cout<<"Le graphe nadmet un cycle eulerien."<<std::endl;
    return 0;
}
