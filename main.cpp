#include <iostream>
#include "graphe.h"
#include "svgfile.h"

int main()
{
    Svgfile svgout;

    graphe g{"broadway.txt","broadway_weights_0.txt"};
    //q2=g.kruskal();
    //g.dessinerKruskal(svgout);
    //g.afficherCasPossible(svgout);
    g.partie3(svgout);
    /*
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
    */
    return 0;
}
