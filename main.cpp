#include <iostream>
#include "graphe.h"
#include "svgfile.h"

int main()
{
    Svgfile svgout;
    std::vector<Arete*> q2;
    int got;
    graphe g{"cubetown.txt","cubetown_weights_0.txt"};
    //q2=g.kruskal();
    g.dessinerKruskal(svgout);
    g.afficherCasPossible();
    for (got = 0; got < q2.size(); ++ got)
        std::cout << q2[got]->getId() << std::endl;
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
