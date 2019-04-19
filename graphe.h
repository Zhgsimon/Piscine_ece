#ifndef GRAPHE_H
#define GRAPHE_H
/*!
* \file graphe.h
* \brief Stockage du graphe r�sultant des fichiers d'entr�es
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
* \brief classe repr�sentant le graphe
* La classe g�re le stockage et les traitements d'un graphe
*/

class graphe
{
    public:
        /*!
        *\brief Constructeur

        * Constructeur de la classe Graphe

        * \param nomFichier : fichier externe de description des sommets
        * \brief format du nomFichier: ordre/liste des id des sommets avec leurs positions/taille/liste des ar�tes avec sommet d�part et sommet arriv�e

        * \param fichierPoids: fichier externe de description des aretes
        * \brief format du fichierPoids: taille/nb de pond�rations/liste des id des aretes/poids des aretes
        */

        graphe(std::string,std::string);

        /*!
        * \brief Destructeur
        * Destructeur de la classe graphe
        */

        ~graphe();
        void afficher() const;
        ///lance un parcours en largeur � partir du sommet d'identifiant id
        void parcoursBFS(std::string) const;
        ///lance et affiche le parcours en largeur � partir du sommet d'identifiant id
        void afficherBFS(std::string) const;
         ///lance un parcours en profondeur � partir du sommet d'identifiant id
        void parcoursDFS(std::string) const;
        ///lance et affiche le parcours en profondeur � partir du sommet d'identifiant id
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
        ///D�termine si un graphe admet une chaine euleriennne
        int isEulerien()const;
        ///Arbre couvrant de poids minimum
        void tri(std::vector<Arete*>& vecteurTri);
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
        * \param cas_possible : tableau des id des aretes parcourus par le cas �tudi�
        * \return true si cas admissible
        * false sinon
        */

        bool Cas_Admissibles(std::vector<std::string> cas_possible);
        float Dijkstra(int idSommet, std::vector<std::string> casActuel);
        void partie3 (Svgfile& svgout);
        std::vector<std::vector<bool>> cas_possibles();
        void afficherCasPossible_Manhattan(Svgfile& svgout);
        bool Cas_Admissibles_Manhattan(std::vector<bool> cas_possible);
        bool testOrdre(std::vector<bool> cas_possible);

    protected:

       private:
        /// Le r�seau est constitu� d'une collection de sommets et d'ar�tes
        std::unordered_map<std::string,Sommet*> m_sommets;/*!<Tous les sommets du graphe stock�s dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)*/
        std::unordered_map<std::string,Arete*> m_aretes; /*!< Toutes les ar�tes du graphe stock�s dans une map (cl�= id de l'ar�te, valeur= pointeur sur l'ar�te)*/
        int m_ordre; /*!< ordre du graphe*/
        int m_taille; /*!<taille du graphe*/

};

#endif // GRAPHE_H
