#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string,std::string);
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
        void dessiner(Svgfile& svgout) const;
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
        void afficherCasPossible();

    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Arete*> m_aretes;
        int m_ordre;
        int m_taille;
};

#endif // GRAPHE_H
