#include <fstream>
#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include <string>
#include <algorithm>
#include <bitset>
#include <cmath>
#define INF INT_MAX ///INFINITE
#include <limits>


graphe::graphe(std::string nomFichier,std::string fichierPoids, int oriente)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
    double x,y;
    m_ordre=ordre;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }
    int taille;
    ifs >> taille;
    m_taille=taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    int id_depart;
    int id_arrive;
    int id_arete;
    float poids1;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
        ifs>>id_arete;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture poids arete");
        ifs>>id_depart;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_arrive;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");
        m_aretes.push_back(new Arete{id_arete,id_depart,id_arrive});
        m_sommets[id_depart]->ajouterVoisin(m_sommets[id_arrive]);
        if (oriente == 0)
            m_sommets[id_arrive]->ajouterVoisin(m_sommets[id_depart]);
    }
    ifs.close();
    std::ifstream ifs2{fichierPoids};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichierPoids );
    ifs2 >> ordre;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    ifs2 >> taille;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    for (int i=0; i< ordre; ++i)
    {
        ifs2>>id_arete;
        for (int j=0; j<taille; ++j)
        {
            ifs2>>poids1;
            m_aretes[id_arete]->ajouterPoids(poids1);
        }
    }
    ifs2.close();
}
void graphe::afficher() const
{
    int numero=0;
    int nbsommet=0;
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"Ordre : "<<m_sommets.size()<<std::endl;
    while ( nbsommet != m_sommets.size()) /// Tant qu'on a pas trouvé le même nombre de sommet que le graphe comporte
    {
        //if( m_sommets[numero]== m_sommets.end()) /// si le sommet existe
        //{
            Sommet*s0=m_sommets[numero]; ///récupation des valeurs puis affichage
            s0->afficherData();
            s0->afficherVoisins();
            nbsommet++;
        //}
        numero++;
        std::cout<<std::endl;
    }
}

void graphe::dessiner(Svgfile& svgout) const {
    ///svgout.addGrid(50,true,"black");
    for (int i=0; i<m_sommets.size();++i)
    {
        svgout.addDisk(m_sommets[i]->getX(), m_sommets[i]->getY(), 10, "black");
    }
    for (int i=0; i<m_aretes.size(); ++i)
    {
        int id_sommetDepart = m_aretes[i]->getSommetDepart();
        int id_sommetArrive = m_aretes[i]->getSommetArrive();
        svgout.addLine(m_sommets[id_sommetDepart]->getX(), m_sommets[id_sommetDepart]->getY(), m_sommets[id_sommetArrive]->getX(), m_sommets[id_sommetArrive]->getY(), "black");
    }
}


bool fonctionTri(const Arete*a1, const Arete*a2)
{
        return a1->getPoids() < a2->getPoids();
}

bool fonctionTri2(const Arete*a1, const Arete*a2)
{
    return a1->getPoids2() < a2->getPoids2();
}

void graphe::tri(std::vector<Arete*>& vecteurTri,int choixPoids)
{
    if (choixPoids == 1)
        std::sort(vecteurTri.begin(),vecteurTri.end(), fonctionTri);
    if (choixPoids == 2)
        std::sort(vecteurTri.begin(),vecteurTri.end(), fonctionTri2);
}


std::vector<Arete*> graphe::kruskal(int choixPoids)
{
    ///Vector avec les id qui ont des poids danss l'ordre croissant
    std::vector<Arete *> vect_tri_croissant;
    std::vector<Arete*>::iterator triArete;
    std::vector<Arete*> arbre_de_poids_minimum;
    std::vector<int> Tableau_connexite;
    int id_sommetDepart;
    int id_sommetArrivee;
    int i=0;
    int j=0;

    for (triArete = m_aretes.begin(); triArete != m_aretes.end(); ++triArete)
    {
        vect_tri_croissant.push_back(*triArete);
    }
    tri(vect_tri_croissant,choixPoids);

    for (auto it= m_sommets.begin(); it != m_sommets.end(); ++it)
    {
        Tableau_connexite.push_back(i);
        ++i;
    }

    while(arbre_de_poids_minimum.size()!=(m_sommets.size())-1)
    {
        id_sommetDepart=vect_tri_croissant[j]->getSommetDepart();
        id_sommetArrivee=vect_tri_croissant[j]->getSommetArrive();
        if((Tableau_connexite[id_sommetDepart]!=(Tableau_connexite[id_sommetArrivee])))
        {
            arbre_de_poids_minimum.push_back(vect_tri_croissant[j]);
            int indice = Tableau_connexite[id_sommetArrivee];
            for (int i = 0; i < Tableau_connexite.size(); ++i)
            {
                if (Tableau_connexite[i] == indice)
                    Tableau_connexite[i] = Tableau_connexite[id_sommetDepart];
            }

        }
        j++;
    }
    return arbre_de_poids_minimum;
}

void graphe::dessinerKruskal(Svgfile& svgout)
{
    int choixPoids=0;
    std::cout << "Quel poids ? 1 ou 2" << std::endl;
    do{
        std::cin >> choixPoids;
    } while (choixPoids !=0 && choixPoids != 1);
    std::vector<Arete*> arbre_de_poids_minimum;
    arbre_de_poids_minimum = kruskal(choixPoids);
    float poids_total;
    for (int i = 0; i < m_sommets.size(); ++i)
    {
        svgout.addDisk(m_sommets[i]->getX(), m_sommets[i]->getY(), 10, "black");
    }
    for (int i = 0; i < arbre_de_poids_minimum.size(); ++i)
    {
        int id_sommetDepart = arbre_de_poids_minimum[i]->getSommetDepart();
        int id_sommetArrive = arbre_de_poids_minimum[i]->getSommetArrive();
        if (choixPoids == 1)
            poids_total += arbre_de_poids_minimum[i]->getPoids();
        if (choixPoids == 2)
            poids_total += arbre_de_poids_minimum[i]->getPoids2();
        svgout.addLine(m_sommets[id_sommetDepart]->getX(), m_sommets[id_sommetDepart]->getY(), m_sommets[id_sommetArrive]->getX(), m_sommets[id_sommetArrive]->getY(), "black");
    }
    svgout.addText(50,50,std::to_string(poids_total),"black");
    std::cout << "Algorihtme de Kruskal effectue"<<std::endl;
}

std::vector<std::vector<bool>> graphe::cas_possibles()
{
    std::vector<std::vector<bool>> conteneur_cas_possibles;
    std::vector<bool> cas_actuel (m_aretes.size());
    ///et j'effectue toutes les combinaisons possibles

    for (int i=0; i<m_sommets.size()-1;++i)
        cas_actuel[i]=1;
    std::sort(cas_actuel.begin(),cas_actuel.end());

    do
    {
        conteneur_cas_possibles.push_back(cas_actuel);
    }while(std::next_permutation(cas_actuel.begin(),cas_actuel.end()));

    std::cout << conteneur_cas_possibles.size() << std::endl;
    return conteneur_cas_possibles;
}

std::vector<std::vector<bool>> graphe::cas_possibles_Partie3()
{
    std::vector<std::vector<bool>> conteneur_cas_possibles;
    std::vector<bool> cas_actuel (m_aretes.size());
    int i=0;
    ///et j'effectue toutes les combinaisons possibles
    for (int j=m_sommets.size()-1; j <= m_aretes.size(); ++j)
    {
        for (int i=0; i < j;++i)
            cas_actuel[i]=1;
        for (int i=j; i < m_aretes.size();++i)
            cas_actuel[i]=0;
        std::sort(cas_actuel.begin(),cas_actuel.end());
        do
        {
            conteneur_cas_possibles.push_back(cas_actuel);
            i++;
            //printf("%d",i);
        }while(std::next_permutation(cas_actuel.begin(),cas_actuel.end()));
        //cas_actuel.clear();
    }
    std::cout << conteneur_cas_possibles.size() << std::endl;
    return conteneur_cas_possibles;
}

bool graphe::Cas_Admissibles_Manhattan(std::vector<bool> cas_possible)
{
    std::vector<int> Tableau_connexite;
    bool admissible=false;
    int compteur=0;
    int cpt=0;
    ///j'initialise mon tableau de connexite
    for(int i=0; i<m_sommets.size();i++)
    {
        Tableau_connexite.push_back(i);
    }
    ///je parcours mon vecteur de bool
    for(int i=0; i != cas_possible.size();i++)
    {
        if(cas_possible[i] == true)
        {
            int sommetDepart = m_aretes[cpt]->getSommetDepart();
            int sommetArrive = m_aretes[cpt]->getSommetArrive();
            if(Tableau_connexite[sommetDepart] != Tableau_connexite[sommetArrive])
            {
                int indice = Tableau_connexite[sommetArrive];
                int stockage = Tableau_connexite[sommetDepart];
                ///parcours des CC de mon tableau de connexite et mise a jour des composantes connexes
                for(int j=0; j<Tableau_connexite.size();++j)
                {
                     if (Tableau_connexite[j] == indice)
                            Tableau_connexite[j] = stockage;
                }
            }
        }
        cpt++;
    }
    int composante_connexe_test = Tableau_connexite[0];
    for(int i=0; i < Tableau_connexite.size();i++)
    {
        int composante_connexe_actuelle = Tableau_connexite[i];
        if(composante_connexe_actuelle == composante_connexe_test)
        {
            compteur++;
        }
    }
    if(compteur == m_sommets.size())
        {
            admissible=true;
        }
    return admissible;
}

void graphe::afficherCasPossible_Manhattan(Svgfile& svgout)
{
    float poidsTotal;
    float poidsTotal2;
    std::vector<std::vector<bool>> recup;
    std::vector<std::vector<bool>> pareto;
    int compteur=0;
    recup=cas_possibles();
    int cpt=0;
    std::vector<float> conteneurPoids1;
    std::vector<float> conteneurPoids2;
    std::vector<int> bonCas;
    std::cout << "__" << recup.size() << "__"<<std::endl;
    ///remplir mon conteneurCasPossible
    for(size_t i=0; i<recup.size();i++)
    {
        poidsTotal=0;
        poidsTotal2=0;
        if (Cas_Admissibles_Manhattan(recup[i]) == true)
        {
            for(size_t j=0;j<recup[i].size();++j)
            {
                if(recup[i][j]==1)
                {
                    poidsTotal = poidsTotal + m_aretes[j]->getPoids();
                    poidsTotal2 = poidsTotal2 + m_aretes[j]->getPoids2();
                }
            ///on insère dans le conteneur
            }
            //std::cout << compteur << std::endl;
            conteneurPoids1.push_back(poidsTotal);
            conteneurPoids2.push_back(poidsTotal2);
            compteur++;
            pareto.push_back(recup[i]);
        }
    }
    double decalage = 0;
    float ampli = 5.0;

    for (int i=0; i < conteneurPoids1.size(); ++i)
    {
        if (conteneurPoids1[i] != 0 && conteneurPoids2[i] != 0)
            for (int j=0; j < conteneurPoids1.size(); ++j)
            {
                if (conteneurPoids1[j] != 0 && conteneurPoids2[j] != 0)
                    if (i!=j)
                        if (conteneurPoids1[i] <= conteneurPoids1[j] && conteneurPoids2[i] <= conteneurPoids2[j])
                        {
                            svgout.addDisk(conteneurPoids1[j]*5,800-conteneurPoids2[j]*5,2,"red");
                            conteneurPoids1[j]=0;
                            conteneurPoids2[j]=0;
                        }
            }
    }
    std::cout<<conteneurPoids1.size()<<std::endl;
    for (int j=0; j < conteneurPoids1.size(); ++j)
    {
        if (conteneurPoids1[j] != 0  && conteneurPoids2[j] != 0)
        {
            svgout.addDisk(conteneurPoids1[j]*5,800-conteneurPoids2[j]*5,2,"green");
            bonCas.push_back(cpt);
            if (j==1)
            {
                svgout.addLine(conteneurPoids1[j]*5-50,800-conteneurPoids2[j]*5+50,conteneurPoids1[j]*5+300,800-conteneurPoids2[j]*5+50,"black");
                svgout.addLine(conteneurPoids1[j]*5-50,800-conteneurPoids2[j]*5+50,conteneurPoids1[j]*5-50,800-conteneurPoids2[j]*5-280,"black");
            }
        }
        cpt++;
    }
    for (int j=0; j < bonCas.size();++j)
    {
        int nombre = bonCas[j];
        for (int i=0; i < m_sommets.size();++i)
        {
            svgout.addDisk(m_sommets[i]->getX()/3 + decalage*120, m_sommets[i]->getY()/3, 1, "black");
        }
        for(size_t j=0; j < pareto[nombre].size(); ++j)
        {
            if( pareto[nombre][j] == 1)
            {
                int id_sommetDepart = m_aretes[j]->getSommetDepart();
                int id_sommetArrive = m_aretes[j]->getSommetArrive();
                svgout.addLine(m_sommets[id_sommetDepart]->getX()/3 +decalage*120, m_sommets[id_sommetDepart]->getY()/3, m_sommets[id_sommetArrive]->getX()/3 +decalage*120, m_sommets[id_sommetArrive]->getY()/3, "black");
            }
        }
        svgout.addText(m_sommets[0]->getX()/3 + decalage*120, m_sommets[0]->getY()/3 + 150, std::to_string(conteneurPoids1[nombre]),"black");
        svgout.addText(m_sommets[0]->getX()/3 + decalage*120, m_sommets[0]->getY()/3 + 180, std::to_string(conteneurPoids2[nombre]),"black");
        decalage++;
    }
}

class prioritize
{
public:
    bool operator ()(std::pair<int, float>&p1,std::pair<int, float>&p2)
    {
        return p1.second>p2.second;
    }
};

void graphe::partie3 (Svgfile& svgout, int oriente)
{
    float poidsTotal;
    float poidsTotal2;
    std::vector<std::vector<bool>> recup;
    std::vector<std::vector<bool>> pareto;
    int compteur=0;
    recup=cas_possibles_Partie3();
    int cpt=0;
    std::vector<float> conteneurPoids1;
    std::vector<float> conteneurPoids2;
    std::vector<int> bonCas;
    std::cout << "__" << recup.size() << "__"<<std::endl;
    ///remplir mon conteneurCasPossible
    for(size_t i=0; i<recup.size();i++)
    {
        poidsTotal=0;
        poidsTotal2=0;
        if (Cas_Admissibles_Manhattan(recup[i]) == true)
        {
            for(size_t j=0;j<recup[i].size();++j)
            {
                if(recup[i][j]==1)
                {
                    poidsTotal = poidsTotal + m_aretes[j]->getPoids();
                }
            ///on insère dans le conteneur
            }
            for (int k=0; k < m_sommets.size(); ++k)
            {
                poidsTotal2 = poidsTotal2 + Dijkstra(k,recup[i], oriente);
            }
            //std::cout << compteur << std::endl;
            conteneurPoids1.push_back(poidsTotal);
            conteneurPoids2.push_back(poidsTotal2);
            compteur++;
            pareto.push_back(recup[i]);
        }
    }
    double decalage = 0;
    float ampli = 5.0;

    for (int i=0; i < conteneurPoids1.size(); ++i)
    {
        if (conteneurPoids1[i] != 0 && conteneurPoids2[i] != 0)
            for (int j=0; j < conteneurPoids1.size(); ++j)
            {
                if (conteneurPoids1[j] != 0 && conteneurPoids2[j] != 0)
                    if (i!=j)
                        if (conteneurPoids1[i] <= conteneurPoids1[j] && conteneurPoids2[i] <= conteneurPoids2[j])
                        {
                            svgout.addDisk(conteneurPoids1[j]*5,800-conteneurPoids2[j]*5,2,"red");
                            conteneurPoids1[j]=0;
                            conteneurPoids2[j]=0;
                        }
            }
    }
    std::cout<<conteneurPoids1.size()<<std::endl;
    for (int j=0; j < conteneurPoids1.size(); ++j)
    {
        if (conteneurPoids1[j] != 0  && conteneurPoids2[j] != 0)
        {
            svgout.addDisk(conteneurPoids1[j]*5,800-conteneurPoids2[j]*5,2,"green");
            bonCas.push_back(cpt);
            if (j==1)
            {
                svgout.addLine(conteneurPoids1[j]*5-50,800-conteneurPoids2[j]*5+50,conteneurPoids1[j]*5+300,800-conteneurPoids2[j]*5+50,"black");
                svgout.addLine(conteneurPoids1[j]*5-50,800-conteneurPoids2[j]*5+50,conteneurPoids1[j]*5-50,800-conteneurPoids2[j]*5-280,"black");
            }
        }
        cpt++;
    }
    for (int j=0; j < bonCas.size();++j)
    {
        int nombre = bonCas[j];
        for (int i=0; i < m_sommets.size();++i)
        {
            svgout.addDisk(m_sommets[i]->getX()/3 + decalage*120, m_sommets[i]->getY()/3, 1, "black");
        }
        for(size_t j=0; j < pareto[nombre].size(); ++j)
        {
            if( pareto[nombre][j] == 1)
            {
                int id_sommetDepart = m_aretes[j]->getSommetDepart();
                int id_sommetArrive = m_aretes[j]->getSommetArrive();
                svgout.addLine(m_sommets[id_sommetDepart]->getX()/3 +decalage*120, m_sommets[id_sommetDepart]->getY()/3, m_sommets[id_sommetArrive]->getX()/3 +decalage*120, m_sommets[id_sommetArrive]->getY()/3, "black");
            }
        }
        svgout.addText(m_sommets[0]->getX()/3 + decalage*120, m_sommets[0]->getY()/3 + 150, std::to_string(conteneurPoids1[nombre]),"black");
        svgout.addText(m_sommets[0]->getX()/3 + decalage*120, m_sommets[0]->getY()/3 + 180, std::to_string(conteneurPoids2[nombre]),"black");
        decalage++;
    }
}

float graphe::Dijkstra(int idSommet , std::vector<bool> casActuel,int oriente)
{
    std::vector<float> Distances(m_sommets.size());
    float recuppoids=0;
    float distanceTotale=0;
    for(float i=0;i<m_sommets.size();i++)
        Distances[i]=10000000.0;
    Distances[idSommet] = 0;
    std::unordered_set< int > marquage;
    std::priority_queue< std::pair <int,float>, std::vector< std::pair <int,float> >, prioritize > file;
    file.push(std::make_pair(idSommet,0));
    while(!file.empty())
    {
        std::pair<int, float> curr = file.top();
        marquage.insert({curr.first});
        file.pop();
        int v = curr.first;
        float w = curr.second;
        for (int i = 0; i < m_sommets[v]->getVoisins().size(); ++i)
        {
            recuppoids=0;
            Sommet* it = m_sommets[v]->getVoisins()[i];
            //std::cout<<m_sommets.find(curr.first)->second->getVoisins().size();
            std::unordered_set<int>::const_iterator got = marquage.find (it->getId());
            if (got == marquage.end())
            {
                for (int j=0; j < casActuel.size(); ++j)
                {
                    if ( casActuel[j] == true )
                    {
                        int sommetDepart = m_aretes[j]->getSommetDepart();
                        int sommetArrive = m_aretes[j]->getSommetArrive();
                        if (oriente == 0)
                            {
                                int sommetDepart2 = m_aretes[j]->getSommetArrive();
                                int sommetArrive2 = m_aretes[j]->getSommetDepart();
                                if ((sommetDepart == curr.first && sommetArrive == it->getId()) || (sommetDepart2 == curr.first && sommetArrive2 == it->getId()))
                                {
                                recuppoids = m_aretes[j]->getPoids2();
                                if ( w + recuppoids < Distances[it->getId()])
                                {
                                    //std::cout<<w<<std::endl;
                                    Distances[it->getId()] =  w + recuppoids ;
                                    file.push(std::make_pair(it->getId(),Distances[it->getId()]));
                                    distanceTotale += Distances[it->getId()];
                                    //printf("_%f_",distanceTotale);
                                }
                                }
                            }
                        if (oriente == 1)
                            if ((sommetDepart == curr.first && sommetArrive == it->getId()))
                            {
                                recuppoids = m_aretes[j]->getPoids2();
                                if ( w + recuppoids < Distances[it->getId()])
                                {
                                    //std::cout<<w<<std::endl;
                                    Distances[it->getId()] =  w + recuppoids ;
                                    file.push(std::make_pair(it->getId(),Distances[it->getId()]));
                                    distanceTotale += Distances[it->getId()];
                                    //printf("_%f_",distanceTotale);
                                }
                            }
                }
            }
        }
    }
}
return distanceTotale;
}

///Dans le sous prog compterBinaire verifier si le vecteur dans le vecteur de vecteur si ce vecteur est non connexe (sous prog de simon et nico ) et le supprimer du vecteur si inutile (erase)

graphe::~graphe()
{
    //dtor
}
