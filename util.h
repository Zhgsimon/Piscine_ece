#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

/*!
* \file util.h
* \brief animation du SVG
* \author Simon Gautier Nicolas
* \version 0.2
*/

#include <string>
#include <random>
#include <ctime>
#include <iostream>
#include <cstdio>

/*! \namespace util
*
* espace de nommage regroupant les outils composants util
*/

namespace util
{
/*! \brief Redirection fichier
*
*  L'appel de cette fonction redirige les
* données du fichier dont le nom est passé
* en paramètre vers std::cin
* On "simule" les frappes clavier ce qui
* permet de tester sans avoir à retaper
*à chaque fois les même données
* L'appel de cette fonction redirige les
* données du fichier dont le nom est passé
*en paramètre vers std::cin
* On "simule" les frappes clavier ce qui
* permet de tester sans avoir à retaper
* à chaque fois les même données
* \param fileName : nom du fichier
* \param temporisation : nombre de milliseconde entre chaque frappe clavier
* \param couleur : colorisation (WINDOWS seulement https://ss64.com/nt/color.html
*/
void startAutoCin(std::string fileName, size_t temporisation=0, short couleur=0);

/*! \brief Retour normal
* Cette fonction doit être appelée pour
* terminer la saisie automatique et retrouver
* un comportement normal (saisir au clavier)
*/

void stopAutoCin();

/// Vide tampon clavier
void videCin();

/*! \brief aleatoire
*
*Cette fonction retourne un entier aléatoire dans [min...max]
* \param min: minimum
*\param max: maximum
* \return un entier compris dans l'ensemble
*/

int alea(int min, int max, std::mt19937& randGen);

/*! \brief aleatoire double
*
*Cette fonction retourne un entier aléatoire dans [min...max]
* \param min: minimum
*\param max: maximum
* \return un double compris dans l'ensemble
*/
double alea(double min, double max, std::mt19937& randGen);

/*! \brief aleatoire
*
*Cette fonction retourne un entier aléatoire dans [min...max]
* \param min: minimum
*\param max: maximum
* \return un entier compris dans l'ensemble
*/

int alea(int min, int max);

/*! \brief aleatoire double
*
*Cette fonction retourne un entier aléatoire dans [min...max]
* \param min: minimum
*\param max: maximum
* \return un double compris dans l'ensemble
*/

double alea(double min, double max);
/// Le code qui suit est spécifique aux plateformes Windows
/// et ne concerne ni macOS ni les Linux
#ifdef _WIN32
void accentsPourWindows();
#endif // _WIN32

}


#endif // UTIL_H_INCLUDED
