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
* \brief classe repr�sentant le sommet
* La classe g�re le stockage et les traitements du sommet
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
        * \param y : position en ordonn�e du sommet
        */

        Sommet(std::string,double,double);
        void ajouterVoisin(Sommet*);
        void afficherData() const;

        /*!
        * \brief Obtention du degr� du sommet
        * M�thode qui permet d'obtenir le nombre de sommets adjacents au sommet
        * \return un entier qui correspond au degr� du sommet
        */

        int getDegre() const;

        /*!
        * \brief Obtention du x du sommet
        * M�thode qui permet d'obtenir la position en abscisse du sommet
        * \return un float qui correspond � l'abscisse du sommet
        */

        int getX() const;

        /*!
        * \brief Obtention du y du sommet
        * M�thode qui permet d'obtenir la position en ordonn�e du sommet
        * \return un float qui correspond � l'ordonn�e du sommet
        */

        int getY() const;

        /*!
        * \brief Obtention des voisins
        * M�thode qui permet d'obtenir l'ensemble des voisins d'un sommet
        * \return un vector de Sommet* qui correspond aux voisins du sommet
        */

        std::vector<Sommet*> getVoisins();

        /*!
        * \brief Obtention de l'ID du sommet
        * M�thode qui permet d'obtenir l'identifiant du sommet
        * \return une chaine de caract�res qui correspond � l'identifiant sommet
        */

        std::string getId() const;
        void afficherVoisins() const;
        ///m�thode de parcours en largeur du graphe � partir du sommet
        ///renvoie les pr�d�cesseurs sous forme d'une map (cl�=id du sommet,valeur=id de son pr�d�cesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///m�thode de parcours en profondeur du graphe � partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///m�thode qui recherche la composante connexe du sommet
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
        std::vector<Sommet*> m_voisins; /*!< Tous les sommets voisins du sommets sont stock�s dans une map (valeur= pointeur sur le sommet voisin)*/
        /// Donn�es sp�cifiques du sommet
        std::string m_id; /*!< Identifiant du sommet*/
        double m_x, m_y; /*!< Position du sommet */


};

#endif // SOMMET_H
