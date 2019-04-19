#include <iostream>
#include "graphe.h"
#include "svgfile.h"

int main()
{
    int choix;
    graphe g{"broadway.txt","broadway_weights_0.txt"};
    do
    {
        std::cout<<"------Bienvenue dans votre generateur------"<<std::endl;
        std::cout<<"------Faites un choix------"<<std::endl;
        std::cout<<"0.Quitter"<<std::endl;
        std::cout<<"1.Afficher votre graphe dans l'output"<<std::endl;
        std::cout<<"2.Afficher tous les cas possibles en console"<<std::endl;
        std::cout<<"3.Afficher l'arbre couvrant de poids minimum"<<std::endl;
        std::cout<<"4.Afficher la frontière de Pareto"<<std::endl;
        std::cout<<"5.Afficher le chemin le plus court de poids minimum"<<std::endl;
        std::cout<<"Votre choix:"<<std::endl;
        std::cin>>choix;
        switch(choix)
        {
        case 0:
            {
                return 0;
                break;
            }
        case 1:
            {
                Svgfile svgout;
                g.dessiner(svgout);
                break;
            }
        case 2:
            {
                Svgfile svgout;
                //g.afficherCasPossible(svgout); en enlevant les commentaires
                break;
            }
        case 3:
            {
                Svgfile svgout;
                g.dessinerKruskal(svgout);
                break;
            }

        case 4:
        {
                Svgfile svgout;
                g.afficherCasPossible_Manhattan(svgout);
                break;
            }
        case 5:
            {
                Svgfile svgout;
                g.partie3(svgout);
                break;
            }
    //q2=g.kruskal();
    //g.dessinerKruskal(svgout);
    //g.afficherCasPossible(svgout);

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
        }
     }while(choix!=0);
    return 0;
}
