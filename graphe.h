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
        void dessiner_partie2_3(Svgfile& svgout,double x_origine,double y_origine) const;

        /*!
        * \brief Dessiner Kruskal
        * Affichage dans l'output de l'arbre couvrant de poids minimum
        */

        void dessinerKruskal(Svgfile& svgout);
        ///Arbre couvrant de poids minimum
        void tri(std::vector<Arete*>& vecteurTri, int choixPoids);
        std::vector<Arete*> kruskal(int choixPoids);

        /*!
        * \brief Chemins possibles
        * Affichage de tous les chemins possibles
        */

        /*!
        * \brief Suppression de chemins
        * Methode qui permet de retirer un cas possible
        * \param cas_possible : tableau des id des aretes parcourus par le cas �tudi�
        * \return true si cas admissible
        * false sinon
        */

        float Dijkstra(int idSommet, std::vector<bool> casActuel,int);
        void partie3 (Svgfile& svgout,int);
        std::vector<std::vector<bool>> cas_possibles();
        void afficherCasPossible_Manhattan(Svgfile& svgout);
        bool Cas_Admissibles_Manhattan(std::vector<bool> cas_possible);
        std::vector<std::vector<bool>> cas_possibles_Partie3();
        float nombreDivise_cout1(float nombre);
        float nombreDivise_cout2(float nombre);

    protected:

       private:
        /// Le r�seau est constitu� d'une collection de sommets et d'ar�tes
        std::vector<Sommet*> m_sommets;/*!<Tous les sommets du graphe stock�s dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)*/
        std::vector<Arete*> m_aretes; /*!< Toutes les ar�tes du graphe stock�s dans une map (cl�= id de l'ar�te, valeur= pointeur sur l'ar�te)*/
        int m_ordre; /*!< ordre du graphe*/
        int m_taille; /*!<taille du graphe*/

};

#endif // GRAPHE_H
