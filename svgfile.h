#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

/*!
* \file svgfile.h
* \brief outil de dessin svg
* \author Simon Gautier Nicolas
* \version 2.0
*/

#include <string>
#include <fstream>
#include <set>


constexpr char defcol[] = "black";

/*! \class Svgfile
* \brief classe representant le dessin svg
*
* La classe gere l'affichage des dessins svg
*/

class Svgfile
{
    public:

        /*!
        * \brief Constructeur
        * Constructeur de la classe Svgfile
        *
        * \param filename : le fichier de sortie du svg
        * \param width : largeur de la fenetre de l'output
        * \param height : longueur de la fenetre de l'output
        */

        Svgfile(std::string _filename = "output.svg", int m_width=2000, int m_height=1000);

        /*!
        * \brief Desctructeur
        *
        * Destructeur de la classe Svgfile
        *
        */

        ~Svgfile();

    void addCloud(double x, double y, double r, std::string color=defcol);

        /*!
        * \brief Creation disque
        *
        * Creation d'un disque sur l'output
        *
        * \param x: abscisse du centre du disque
        * \param y: ordonnée du centre du disque
        * \param r: rayon du disque
        * \param color : couleur du disque
        *
        */
        void addDisk(double x, double y, double r, std::string color=defcol);

        /*!
        * \brief Creation cercle
        *
        * Creation d'un cercle sur l'output
        *
        * \param x: abscisse du centre du cercle
        * \param y: ordonnée du centre du cercle
        * \param r: rayon du cercle
        * \param ep: epaisseur du cercle
        * \param color : couleur du cercle
        *
        */
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);


        void addEllipse(double x, double y, double rx,double ry, double ep, std::string color=defcol);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        /*!
        * \brief Creation ligne
        *
        * Creation d'une ligne sur l'output
        *
        * \param x1 : abscisse du point de depart de la ligne
        * \param y1 : ordonnee du point de depart de la ligne
        * \param x2 : abscisse du point d'arrivee de la ligne
        * \param y2 : ordonnee du point d'arrivee de la ligne
        * \param color: couleur de la ligne
        *
        */
        void addLine(double x1, double y1, double x2, double y2,std::string color=defcol);
        void addLineEp(double x1, double y1, double x2, double y2, double ep, std::string color=defcol);

        void addCross(double x, double y, double span, std::string color=defcol);
        void addTree(double x, double y,double r, std::string color=defcol);

        /*!
        * \brief Creation texte
        *
        * Creation d'un texte quelconque dans l'output
        *
        * \param x : abscisse du debut du texte
        * \param y : ordonnee du debut du texte
        * \param text : la chaine de caracteres à afficher dans l'output
        * \param color : couleur du texte
        *
        */

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);
        void addCurve();
        void addSoleil( double r, std::string color=defcol);
        void addRectangle(double x1, double y1, double x2, double y2,
                          double x3, double y3,double x4, double y4, std::string colorFill);

        void addEllipseB(double x, double y, double rx,double ry ,double ep, std::string color);

        /*!
        * \brief Creation grille
        *
        * Creation d'une grille dans l'output
        *
        * \param span : ecart entre les lignes de la grille
        * \param numbering: ajout ou non de la valeur des ordonnes et abscisses
        * \param color : couleur de la grille
        */
        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        void addBush(double x, double y, double taille,std::string color );

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

        static bool s_verbose;

    private:
        std::string m_filename; /*!< nom du fichier*/
        std::ofstream m_ostrm;
        int m_width; /*!< taille de la largeur */
        int m_height; /*!< taille de la longueur */

        static std::set<std::string> s_openfiles; /*!< Pour éviter les ouverture multiples*/
};

#endif // SVGFILE_H_INCLUDED



