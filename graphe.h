#ifndef GRAPHE_H
#define GRAPHE_H
/*!
* \file graphe.h
* \brief Stockage du graphe résultant des fichiers d'entrées
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
* \brief classe représentant le graphe
* La classe gère le stockage et les traitements d'un graphe
*/

class graphe
{
    public:
        /*!
        *\brief Constructeur

        * Constructeur de la classe Graphe

        * \param nomFichier : fichier externe de description des sommets
        * \brief format du nomFichier: ordre/liste des id des sommets avec leurs positions/taille/liste des arêtes avec sommet départ et sommet arrivée

        * \param fichierPoids: fichier externe de description des aretes
        * \brief format du fichierPoids: taille/nb de pondérations/liste des id des aretes/poids des aretes
        */

        graphe(std::string,std::string,int);

        /*!
        * \brief Destructeur
        * Destructeur de la classe graphe
        */

        ~graphe();
        void afficher() const;

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
        ///Arbre couvrant de poids minimum
        void tri(std::vector<Arete*>& vecteurTri, int choixPoids);
        std::vector<Arete*> kruskal(int choixPoids);
        //std::vector<std::vector<std::string>> compterBinaire();

        /*!
        * \brief Chemins possibles
        * Affichage de tous les chemins possibles
        */

        //void afficherCasPossible(Svgfile& svgout);

        /*!
        * \brief Suppression de chemins
        * Methode qui permet de retirer un cas possible
        * \param cas_possible : tableau des id des aretes parcourus par le cas étudié
        * \return true si cas admissible
        * false sinon
        */

        //bool Cas_Admissibles(std::vector<std::string> cas_possible);
        float Dijkstra(int idSommet, std::vector<bool> casActuel,int);
        void partie3 (Svgfile& svgout,int);
        std::vector<std::vector<bool>> cas_possibles();
        void afficherCasPossible_Manhattan(Svgfile& svgout);
        bool Cas_Admissibles_Manhattan(std::vector<bool> cas_possible);
        std::vector<std::vector<bool>> cas_possibles_Partie3();

    protected:

       private:
        /// Le réseau est constitué d'une collection de sommets et d'arêtes
        std::vector<Sommet*> m_sommets;/*!<Tous les sommets du graphe stockés dans une map (clé=id du sommet, valeur= pointeur sur le sommet)*/
        std::vector<Arete*> m_aretes; /*!< Toutes les arêtes du graphe stockés dans une map (clé= id de l'arête, valeur= pointeur sur l'arête)*/
        int m_ordre; /*!< ordre du graphe*/
        int m_taille; /*!<taille du graphe*/

};

#endif // GRAPHE_H
