#ifndef SOMMET_H
#define SOMMET_H

/*!
* \file sommet.h
* \brief Stockage du sommet
* \author Simon Gautier Nicolas
*\version 1.2
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"

/*!
* \class Sommet
* \brief classe representant le sommet
* La classe gere le stockage et les traitements du sommet
*/

class Sommet
{
    public:

        /*!
        * \brief Constructeur de la classe Sommet
        *
        * \param id : identifiant du sommet
        *
        * \param x : position en abscisse du sommet
        *
        * \param y : position en ordonnée du sommet
        */

        Sommet(std::string,double,double);
        void ajouterVoisin(Sommet*);

        /*!
        * \brief Affichage des donnees Sommet
        * affichage de l'identifiant et de la position d'un sommet
        */

        void afficherData() const;

        /*!
        * \brief Obtention du degre du sommet
        * Methode qui permet d'obtenir le nombre de sommets adjacents au sommet
        * \return un entier qui correspond au degre du sommet
        */

        int getDegre() const;

        /*!
        * \brief Obtention du x du sommet
        * Methode qui permet d'obtenir la position en abscisse du sommet
        * \return un float qui correspond à l'abscisse du sommet
        */

        int getX() const;

        /*!
        * \brief Obtention du y du sommet
        * Méthode qui permet d'obtenir la position en ordonnee du sommet
        * \return un float qui correspond à l'ordonnee du sommet
        */

        int getY() const;

        /*!
        * \brief Obtention des voisins
        * Methode qui permet d'obtenir l'ensemble des voisins d'un sommet
        * \return un vector de Sommet* qui correspond aux voisins du sommet
        */

        std::vector<Sommet*> getVoisins();

        /*!
        * \brief Obtention de l'ID du sommet
        * Methode qui permet d'obtenir l'identifiant du sommet
        * \return une chaine de caracteres qui correspond à l'identifiant sommet
        */

        std::string getId() const;

        /*!
        * \brief affichage voisisns console
        * Affichage des voisins d'un sommet en console avec toutes ses composantes (id + positions)
        */
        void afficherVoisins() const;


        ///méthode de parcours en largeur du graphe à partir du sommet
        ///renvoie les prédécesseurs sous forme d'une map (clé=id du sommet,valeur=id de son prédécesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///méthode de parcours en profondeur du graphe à partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///méthode qui recherche la composante connexe du sommet
        ///renvoie la liste des ids des sommets de la composante
        std::unordered_set<std::string> rechercherCC() const;


        /*!
        * \brief Destructeur
        * Destructeur de la classe Sommet
        */

        ~Sommet();

    protected:

        private:
        /// Voisinage : liste d'adjacence
        std::vector<Sommet*> m_voisins; /*!< Tous les sommets voisins du sommets sont stockes dans une map (valeur= pointeur sur le sommet voisin)*/
        /// Donnees specifiques du sommet
        std::string m_id; /*!< Identifiant du sommet*/
        double m_x, m_y; /*!< Position du sommet */


};

#endif // SOMMET_H
