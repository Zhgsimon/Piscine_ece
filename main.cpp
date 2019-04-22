#include <iostream>
#include "graphe.h"
#include "svgfile.h"

int main()
{
    int choix;
    int oriente;
    do
    {
        std::string fichierchoisi;
        std:: string extension1=".txt";
        std::string extension2="_weights_0.txt";
        std::string nomfichierchoisi;
        std::string nomfichierpoids;
        std::cout<<"Quel fichier allez-vous choisir?"<<std::endl;
        std::cin>>fichierchoisi;
        std::cout << "Oriente:1 / Non-oriente:0 . Votre choix : " ;
        do {
            std::cin >> oriente;
        }while (oriente !=1 && oriente !=0);
        nomfichierchoisi= fichierchoisi+extension1;
        nomfichierpoids=fichierchoisi+extension2;
        graphe g{nomfichierchoisi,nomfichierpoids,oriente};
        std::cout<<"------Bienvenue dans votre generateur------"<<std::endl;
        std::cout<<"------Faites un choix------"<<std::endl;
        std::cout<<"0.Quitter"<<std::endl;
        std::cout<<"1.Afficher votre graphe dans l'output"<<std::endl;
        std::cout<<"2.Afficher tous les cas possibles en console"<<std::endl;
        std::cout<<"3.Afficher l'arbre couvrant de poids minimum"<<std::endl;
        std::cout<<"4.Afficher le chemin le plus court de poids minimum"<<std::endl;
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
                g.afficherCasPossible_Manhattan(svgout);
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
                g.partie3(svgout,oriente);
                break;
            }
        }
     }while(choix!=0);
    return 0;
}

