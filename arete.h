#ifndef ARETE_H
#define ARETE_H

/*!
* \file arete.h
* \brief Stockage de l'arete
* \author Simon Gautier Nicolas
* \version 0.5
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/*! \class Arete
* \brief classe repr�sentant l'arete
*
* La classe g�re le stockage et les traitements de l'arete
*/
class Arete
{
    public:
        /*!
        *  \brief Constructeur
        *
        *  Constructeur de la classe Arete
        *
        *  \param id : identifiant de l'arete
        *
        * \param sommet_depart : identifiant du sommet de depart de l'arete
        *
        * \param sommet_arrive : identifiant du sommet d'arrivee de l'arete
        */
        Arete(int id, int sommet_depart, int sommet_arrive);

        /*!
        * \brief Ajoute un poids
        *
        * ajoute un poids en parametre au vector de poids de la classe arete
        */

        void ajouterPoids(float poids);

        /*!
        * \brief Obtention du poids1 de l'arete
        * M�thode qui permet d'obtenir le poids1 de l'arete
        * \return un float qui correspond au poids 1 de l'arete
        */
        float getPoids()const;

        /*!
        * \brief Obtention du poids2 de l'arete
        * M�thode qui permet d'obtenir le poids2 de l'arete
        * \return un float qui correspond au poids 2 de l'arete
        */

        float getPoids2()const;

        /*!
        * \brief Obtention de l'ID du sommet de depart de l'arete
        * M�thode qui permet d'obtenir l'identifiant du sommet de depart de l'arete
        * \return une chaine de caract�res qui correspond � l'identifiant sommet de depart de l'arete
        */
        int getSommetDepart() const;

        /*!
        * \brief Obtention de l'ID du sommet de'arrivee de l'arete
        * M�thode qui permet d'obtenir l'identifiant du sommet d'arrivee de l'arete
        * \return une chaine de caract�res qui correspond � l'identifiant sommet de'arrivee de l'arete
        */
        int getSommetArrive() const;

        /*!
        * \brief Obtention de l'ID de l'arete
        * M�thode qui permet d'obtenir l'identifiant de l'arete
        * \return une chaine de caract�res qui correspond � l'identifiant de l'arete
        */

        int getId() const;

        /*!
        * \brief Destructeur
        * Destructeur de la classe Arete
        */
        virtual ~Arete();

    private:
        int m_id; /*!< Identifiant de l'arete*/
        std::vector<float> m_poids; /*!< Vecteur des poids flottants de l'arete (dans notre cas le cout et la distance)*/
        int m_sommet_depart; /*!< chaine de caracteres correspondant � l'Identifiant du sommet de depart de l'arete*/
        int m_sommet_arrive; /*!< chaine de caracteres correspondant � l'Identifiant du sommet de depart de l'arete*/
};

#endif // ARETE_H
