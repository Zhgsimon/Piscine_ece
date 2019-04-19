#ifndef GRAPHE_H
#define GRAPHE_H
/*!
* \file graphe.h
* \brief Stockage du graphe resultant des fichiers d'entrees
* \author Simon Gautier Nicolas
* \version 0.5
*/

#include <string>
#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"
#include <limits>

/*! \class graphe
* \brief classe representant le graphe
* La classe gere le stockage et les traitements d'un graphe
*/

class graphe
{
    public:
        /*!
        *\brief Constructeur

        * Constructeur de la classe Graphe

        * \param nomFichier : fichier externe de description des sommets
        * \brief format du nomFichier: ordre/liste des id des sommets avec leurs positions/taille/liste des arêtes avec sommet départ et sommet arrivee

        * \param fichierPoids: fichier externe de description des aretes
        * \brief format du fichierPoids: taille/nb de ponderations/liste des id des aretes/poids des aretes
        */

        graphe(std::string,std::string);

        /*!
        * \brief Destructeur
        * Destructeur de la classe graphe
        */

        ~graphe();

        /*!
        * \brief Affichage graphe console
        * Affichage d'un graphe en console avec toutes ses composantes (sommets + positions + voisins)
        */

        void afficher() const;

        ///lance un parcours en largeur à partir du sommet d'identifiant id
        void parcoursBFS(std::string) const;
        ///lance et affiche le parcours en largeur à partir du sommet d'identifiant id
        void afficherBFS(std::string) const;
         ///lance un parcours en profondeur à partir du sommet d'identifiant id
        void parcoursDFS(std::string) const;
        ///lance et affiche le parcours en profondeur à partir du sommet d'identifiant id
        void afficherDFS(std::string) const;


        /*!
        * \brief Dessiner
        * Affichage dans l'output du graphe
        */

        void dessiner(Svgfile& svgout) const;

        /*!
        * \brief Dessiner Kruskal
        * Affichage dans l'output de l'arbre couvrant de poids minimum
        */

        void dessinerKruskal(Svgfile& svgout);

        ///recherche et affiche les composantes connexes
        ///retourne le nombre de composantes connexes
        int rechercher_afficherToutesCC() const;
        ///Détermine si un graphe admet une chaine euleriennne
        int isEulerien()const;

        ///Arbre couvrant de poids minimum

        /*!
        * \brief Trier
        * Tri d'un vecteur d'aretes dans l'ordre croissant
        */


        void tri(std::vector<Arete*>& vecteurTri);

        /*!
        * \brief Determine l'arbre de poids mini
        * Tri des aretes appartenant à l'arbre couvrant de poids minimum
        * \return un vecteur d'aretes* contenant toutes les aretes couvrantes de poids minimum
        */

        std::vector<Arete*> kruskal();




        std::vector<std::vector<std::string>> compterBinaire();

        /*!
        * \brief Chemins possibles
        * Affichage de tous les chemins possibles
        */

        void afficherCasPossible(Svgfile& svgout);

        /*!
        * \brief Suppression de chemins
        * Methode qui permet de retirer un cas possible
        * \param cas_possible : tableau des id des aretes parcourus par le cas etudie
        * \return true si cas admissible
        * false sinon
        */

        bool Cas_Admissibles(std::vector<std::string> cas_possible);

        /*!
        * \brief Calcul distance Djikstra
        * Methode qui permet de calculer la somme des temps de parcours des cas admissibles
        * \param idSommet: l'identifiant du sommet de depart
        * \param casActuel: vecteur contenant les aretes des cas admissibles
        * \return un float correspondant à la distance totale
        *
        */

        float Dijkstra(int idSommet, std::vector<std::string> casActuel);

        /*!
        * \brief Affichage du pareto selon deux objectifs
        * Affichage du resultat obtenu par Djikstra et determination du pareto bi-objectif
        *
        */

        void partie3 (Svgfile& svgout);


    protected:

       private:
        /// Le réseau est constitue d'une collection de sommets et d'aretes
        std::unordered_map<std::string,Sommet*> m_sommets;/*!<Tous les sommets du graphe stockes dans une map (cle=id du sommet, valeur= pointeur sur le sommet)*/
        std::unordered_map<std::string,Arete*> m_aretes; /*!< Toutes les aretes du graphe stockes dans une map (cle= id de l'arete, valeur= pointeur sur l'arete)*/
        int m_ordre; /*!< ordre du graphe*/
        int m_taille; /*!<taille du graphe*/

};

#endif // GRAPHE_H
