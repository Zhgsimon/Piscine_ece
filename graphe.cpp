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


graphe::graphe(std::string nomFichier,std::string fichierPoids)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
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
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    m_taille=taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_depart;
    std::string id_arrive;
    std::string id_arete;
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
        m_aretes.insert({id_arete,new Arete{id_arete,id_depart,id_arrive}});
        (m_sommets.find(id_depart))->second->ajouterVoisin((m_sommets.find(id_arrive))->second);
        (m_sommets.find(id_arrive))->second->ajouterVoisin((m_sommets.find(id_depart))->second);
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
            (m_aretes.find(id_arete))->second->ajouterPoids(poids1);
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
        if(m_sommets.find(std::to_string(numero))!=m_sommets.end()) /// si le sommet existe
        {
            Sommet*s0=(m_sommets.find(std::to_string(numero)))->second; ///récupation des valeurs puis affichage
            s0->afficherData();
            s0->afficherVoisins();
            nbsommet++;
        }
        numero++;
        std::cout<<std::endl;
    }
}

void graphe::parcoursBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}
void graphe::afficherBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
int graphe::rechercher_afficherToutesCC() const
{
    int i=0;
    int compteursommet=0;
    int nbsommet=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set<std::string> recup;
    std::unordered_set<std::string> save;
    while (nbsommet != m_sommets.size())
    {
        if (save.find(std::to_string(compteursommet))==save.end()) /// si le sommet est non marqué
        {
            i++;
            Sommet*s0=(m_sommets.find(std::to_string(compteursommet)))->second;
            recup=s0->rechercherCC();  ///on récupère une composante connexe
            std::unordered_set<std::string> :: iterator itr;
            std::cout<<"cc"<<i<<std::endl;
            for (itr = recup.begin(); itr != recup.end(); itr++)
            {
                std::cout << (*itr) <<"    "; ///affichage de la composante connexe
                save.insert(*itr);   ///marquage des sommets de cette composante dans un unordered_set
                nbsommet++;
            }
            std::cout<<std::endl;
            compteursommet++;
        }
        else
            compteursommet++;
    }
    return i;
}

int graphe::isEulerien()const
{
    int numero=0;
    int degreimpair=0;
    int nbsommet=0;
    int degre=0;
    std::vector<std::string> liste_impair;
    std::unordered_set<std::string> recup;
    while (nbsommet != m_sommets.size())
    {
        if(m_sommets.find(std::to_string(numero))!=m_sommets.end()) /// si le sommet existe dans m_sommets
        {
            Sommet*s0=(m_sommets.find(std::to_string(numero)))->second;
            degre=s0->getDegre(); /// on recupre son degre
            if (degre%2 != 0) ///si le degre est impair
            {
                degreimpair++;  ///on incremente degreimpair
                liste_impair.push_back(std::to_string(numero));   ///et on sauvegarde l'id du sommet en question
            }
            nbsommet++;
        }
        numero++;
    }
    if (degreimpair == 0) /// cycle eulérien
        return 2;
    if (degreimpair ==2)  /// chaine eulérienne
    {
        std::vector<std::string> :: iterator itr;
        std::cout <<"Les extremites sont : ";
        for (itr = liste_impair.begin(); itr != liste_impair.end(); itr++) /// affichage des extrémités
        {
            std::cout <<(*itr) <<"    ";
        }
        return 1;
    }
    if (degreimpair!=0 && degreimpair!=2) /// rien d'eulerien
        return 0;
}

void graphe::dessiner(Svgfile& svgout) const {
    ///svgout.addGrid(50,true,"black");
    for (int i=0; i<m_sommets.size();++i)
    {
        svgout.addDisk(m_sommets.find(std::to_string(i))->second->getX(), m_sommets.find(std::to_string(i))->second->getY(), 10, "red");
    }
    for (int i=0; i<m_aretes.size(); ++i)
    {
        std::string id_sommetDepart = m_aretes.find(std::to_string(i))->second->getSommetDepart();
        std::string id_sommetArrive = m_aretes.find(std::to_string(i))->second->getSommetArrive();
        svgout.addLine(m_sommets.find(id_sommetDepart)->second->getX(), m_sommets.find(id_sommetDepart)->second->getY(), m_sommets.find(id_sommetArrive)->second->getX(), m_sommets.find(id_sommetArrive)->second->getY(), "blue");
    }
}


bool fonctionTri(const Arete*a1, const Arete*a2)
{
    return a1->getPoids() < a2->getPoids();
}

void graphe::tri(std::vector<Arete*>& vecteurTri)
{
    std::sort(vecteurTri.begin(),vecteurTri.end(), fonctionTri);
}


std::vector<Arete*> graphe::kruskal()
{
    ///Vector avec les id qui ont des poids danss l'ordre croissant
    std::vector<Arete *> vect_tri_croissant;
    std::unordered_map<std::string,Arete*>::iterator triArete;
    //vect_tri_croissant=triCroissant();
    std::vector<Arete *> arbre_de_poids_minimum;
    std::unordered_map<std::string,int> Tableau_connexite;
    std::string id_sommetDepart;
    std::string id_sommetArrivee;
    int i=0;
    int j=0;

    for (triArete = m_aretes.begin(); triArete != m_aretes.end(); ++triArete)
    {
        vect_tri_croissant.push_back(triArete->second);
    }
    tri(vect_tri_croissant);

    for (auto it= m_sommets.begin(); it != m_sommets.end(); ++it)
    {
        Tableau_connexite.insert({it->second->getId(),i});
        ++i;
    }

    while(arbre_de_poids_minimum.size()!=(m_sommets.size())-1)
    {
        id_sommetDepart=vect_tri_croissant[j]->getSommetDepart();
        id_sommetArrivee=vect_tri_croissant[j]->getSommetArrive();
        if((Tableau_connexite.find(id_sommetDepart))->second!=(Tableau_connexite.find(id_sommetArrivee)->second))
        {
            arbre_de_poids_minimum.push_back(vect_tri_croissant[j]);
            int indice = Tableau_connexite[id_sommetArrivee];
            for (int i = 0; i < Tableau_connexite.size(); ++i)
            {
                if (Tableau_connexite.find(std::to_string(i))->second == indice)
                    Tableau_connexite[std::to_string(i)] = Tableau_connexite.find(id_sommetDepart)->second;
            }

        }
        j++;
    }
    return arbre_de_poids_minimum;
}

void graphe::dessinerKruskal(Svgfile& svgout)
{
    std::vector<Arete *> arbre_de_poids_minimum;
    arbre_de_poids_minimum = kruskal();
    //svgout.addGrid(50,true,"black");
    for (int i = 0; i < m_sommets.size(); ++i)
    {
        svgout.addDisk(m_sommets.find(std::to_string(i))->second->getX(), m_sommets.find(std::to_string(i))->second->getY(), 10, "black");
    }
    for (int i = 0; i < arbre_de_poids_minimum.size(); ++i)
    {
        std::string id_sommetDepart = arbre_de_poids_minimum[i]->getSommetDepart();
        std::string id_sommetArrive = arbre_de_poids_minimum[i]->getSommetArrive();
        svgout.addLine(m_sommets.find(id_sommetDepart)->second->getX(), m_sommets.find(id_sommetDepart)->second->getY(), m_sommets.find(id_sommetArrive)->second->getX(), m_sommets.find(id_sommetArrive)->second->getY(), "black");
        svgout.addLine(m_sommets.find(id_sommetArrive)->second->getX()-20, m_sommets.find(id_sommetArrive)->second->getY()-20, m_sommets.find(id_sommetArrive)->second->getX(), m_sommets.find(id_sommetArrive)->second->getY(), "black");
        svgout.addLine(m_sommets.find(id_sommetArrive)->second->getX()+20, m_sommets.find(id_sommetArrive)->second->getY()+20, m_sommets.find(id_sommetArrive)->second->getX(), m_sommets.find(id_sommetArrive)->second->getY(), "black");
    }
}
bool graphe::testOrdre(std::vector<bool> cas_possible)
{
    int compteur=0;
    bool ordre;
    for(int i=0; i<cas_possible.size();i++)
        if(cas_possible[i]==true)
            compteur++;
    if (compteur >= m_sommets.size()-1) ordre= true;
    else ordre= false;
    return ordre;
}
std::vector<std::vector<bool>> graphe::cas_possibles()
{
    std::vector<std::vector<bool>> conteneur_cas_possibles;

    std::vector<bool> cas_actuel (m_aretes.size());
    ///et j'effectue toutes les combinaisons possibles
    for (int i=0; i<m_sommets.size()-1;++i)
        cas_actuel[m_sommets.size()-i]=1;
    for (int i=cas_actuel.size(); i<m_aretes.size()-1;++i)
        cas_actuel[m_sommets.size()-i]=0;
    do
    {
        conteneur_cas_possibles.push_back(cas_actuel);
    }while(std::next_permutation(cas_actuel.begin(),cas_actuel.end()));
    std::cout << conteneur_cas_possibles.size() << std::endl;
    return conteneur_cas_possibles;
}

bool graphe::Cas_Admissibles_Manhattan(std::vector<bool> cas_possible)
{
    std::string sommetDepart;
    std::string sommetArrive;
    std::unordered_map<std::string,int> Tableau_connexite;
    bool admissible=false;
    int composante_connexe_test;
    int composante_connexe_actuelle;
    int i=0;
    int compteur=0;
    ///j'initialise mon tableau de connexite
    for(int i=0; i<m_sommets.size();i++)
    {
        Tableau_connexite.insert({m_sommets.find(std::to_string(i))->second->getId(),i});
    }

    ///je parcours mon vecteur de bool
    for(int i=0; i<cas_possible.size();i++)
    {
        if(cas_possible[i]==true)
        {
            sommetDepart=m_aretes.find(std::to_string(i))->second->getSommetDepart();
            sommetArrive=m_aretes.find(std::to_string(i))->second->getSommetArrive();

            if(Tableau_connexite.find(sommetDepart)->second!=Tableau_connexite.find(sommetArrive)->second)
            {
                ///parcours des CC de mon tableau de connexite et mise a jour des composantes connexes
                for(int j=0; j<Tableau_connexite.size();++j)
                {
                     if (Tableau_connexite.find(std::to_string(j))->second == Tableau_connexite.find(sommetArrive)->second)
                            Tableau_connexite[std::to_string(j)] = Tableau_connexite.find(sommetDepart)->second;
                }
            }
        }
    }
    composante_connexe_test=Tableau_connexite.find("0")->second;
    for(int i=0; i<Tableau_connexite.size();i++)
    {

        composante_connexe_actuelle=Tableau_connexite.find(std::to_string(i))->second;
        if(composante_connexe_actuelle==composante_connexe_test)
        {
            compteur++;///booleen + break
        }
    }
    if(compteur==Tableau_connexite.size())
        admissible=true;
    return admissible;
}

void graphe::afficherCasPossible_Manhattan(Svgfile& svgout)
{
    std::vector<float> recupPoids;

    float poidsTotal;
    float poidsTotal2;


    std::vector<std::vector<bool>> recup;
    std::vector<float> poids_total_cas_possible;
    std::vector<float> poids_total2_cas_possible;

    recup=cas_possibles();

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
                    poidsTotal=poidsTotal+m_aretes.find(std::to_string(j))->second->getPoids();
                    poidsTotal2=poidsTotal2+m_aretes.find(std::to_string(j))->second->getPoids2();
                }
            ///on insère dans le conteneur
            poids_total_cas_possible.push_back(poidsTotal);
            poids_total2_cas_possible.push_back(poidsTotal2);
            }
        }
    }
/*
    for(size_t i=0; i< poids_total_cas_possible.size();i++ )
    {
        for(size_t j=0; j<poids_total_cas_possible.size(); j++)
        {
            if(poids_total_cas_possible[i]<poids_total_cas_possible[j] && poids_total2_cas_possible[i] < poids_total2_cas_possible[j])
            {
                svgout.addDisk(poids_total_cas_possible[j]*10,600-poids_total2_cas_possible[j]*10,5,"red");
            }
        }
    }*/
}


std::vector<std::vector<std::string>> graphe::compterBinaire()
{
    double nb_depart = pow(2.0,m_aretes.size());
    std::vector<std::vector<std::string>> casPossible(nb_depart);
    for (int i=0; i < nb_depart; ++i)
    {
        int a = i;
        for (int j = m_aretes.size(); j >= 0; --j)
        {
            if (a >= pow(2,j))
            {
                casPossible[i].push_back(std::to_string(j));
                a = a - pow(2,j);
            }
        }
            //casPossible.erase(casPossible[i]);
    }
    return casPossible;
}

bool graphe::Cas_Admissibles(std::vector<std::string> cas_possible)
{
    bool admissible;
    std::unordered_set<std::string> marquage;
    std::vector<std::string>::iterator i;
    for(i = cas_possible.begin(); i != cas_possible.end(); i++)
    {
        std::string recupSommetDepart = m_aretes.find(*i)->second->getSommetDepart();
        std::unordered_set<std::string>::const_iterator got = marquage.find (recupSommetDepart);
        if (got == marquage.end())
            marquage.insert(recupSommetDepart);

        std::string recupSommetArrive = m_aretes.find(*i)->second->getSommetArrive();
        std::unordered_set<std::string>::const_iterator get = marquage.find (recupSommetArrive);
        if (get == marquage.end())
            marquage.insert(recupSommetArrive);
    }
    if(cas_possible.size()>=m_sommets.size()-1 && marquage.size()== m_sommets.size())
    {
        admissible=true;
    }

    else
    {
        admissible=false;
    }

    return admissible;
}

void graphe::afficherCasPossible(Svgfile& svgout)
{
    std::vector<std::vector<std::string>> recup;
    std::vector<float> recupPoids;
    std::unordered_map<int,std::vector<float>> conteneurCasPossible;
    recup = compterBinaire();
    int compteur=0;
    std::unordered_map<int,std::vector<float>>::const_iterator var1;
    std::unordered_map<int,std::vector<float>>::const_iterator var2;
    for (size_t i=0; i< recup.size(); ++i)
    {
        float poidsTotal=0;
        float poidsTotal2=0;
        std::cout << "Cas "<<compteur<<" : ";
        for (size_t j=0; j < recup[i].size(); ++j)
        {
             std::cout << recup[i][j] <<"  " ;
             poidsTotal = poidsTotal + m_aretes.find(recup[i][j])->second->getPoids();
             poidsTotal2 = poidsTotal2 + m_aretes.find(recup[i][j])->second->getPoids2();
        }
        recupPoids.push_back(poidsTotal);
        recupPoids.push_back(poidsTotal2);
        if (Cas_Admissibles(recup[i]) == true)
            conteneurCasPossible.insert({compteur,recupPoids});
        recupPoids.clear();
        std::cout <<"Poids Total : " << "(" <<poidsTotal<<","<<poidsTotal2<<")";
        compteur++;
        std::cout << std::endl;
    }
    std::cout << conteneurCasPossible.size();
    std::cout << "ok";
    svgout.addLine(10,400,300,400,"black");
    for (var1 = conteneurCasPossible.begin(); var1 != conteneurCasPossible.end(); var1++)
    {
        for (var2 = conteneurCasPossible.begin(); var2 != conteneurCasPossible.end(); var2++)
        {
            if (var1->second[0] < var2->second[0] && var1->second[1] < var2->second[1])
            {
                svgout.addDisk(var2->second[0]*10,600-var2->second[1]*10,5,"red");
                conteneurCasPossible.erase(var2);
            }
        }
    }
    for (var1 = conteneurCasPossible.begin(); var1 != conteneurCasPossible.end(); var1++)
    {
        svgout.addDisk(var1->second[0]*10,600-var1->second[1]*10,5,"green");
        printf("test");
    }
}

bool triPoidsArete(const Arete*a1, const Arete*a2)
{
    return a1->getPoids() < a2->getPoids();
}

class prioritize
{
public:
    bool operator ()(std::pair<std::string, float>&p1,std::pair<std::string, float>&p2)
    {
        return p1.second>p2.second;
    }
};

void graphe::partie3 (Svgfile& svgout)
{
    std::vector<std::vector<std::string>> recup;
    std::vector<float> recupPoids;
    std::unordered_map<int,std::vector<float>> conteneurCasPossible;
    recup = compterBinaire();
    int compteur=0;
    float recipient=0;
    std::unordered_map<int,std::vector<float>>::iterator var1;
    std::unordered_map<int,std::vector<float>>::iterator var2;
    for (size_t i=0; i< recup.size(); ++i)
    {
        float poidsTotal=0;
        float poidsTotal2=0;
        std::cout << "Cas "<<compteur<<" : ";
        for (size_t j=0; j < recup[i].size(); ++j)
        {
             std::cout << recup[i][j] <<"  " ;
             poidsTotal = poidsTotal + m_aretes.find(recup[i][j])->second->getPoids();
        }
        for (int k=0; k < m_sommets.size(); ++k)
        {
                poidsTotal2 = poidsTotal2 + Dijkstra(k,recup[i]);
        }
        recupPoids.push_back(poidsTotal);
        recupPoids.push_back(poidsTotal2);
        if (Cas_Admissibles(recup[i]) == true)
            conteneurCasPossible.insert({compteur,recupPoids});
        recupPoids.clear();
        std::cout <<"Poids Total : " << "(" <<poidsTotal<<","<<poidsTotal2<<")";
        compteur++;
        std::cout << std::endl;
    }
    std::cout << "ok";
    svgout.addLine(10,400,300,400,"black");
    for (var1 = conteneurCasPossible.begin(); var1 != conteneurCasPossible.end(); var1++)
    {
        for (var2 = conteneurCasPossible.begin(); var2 != conteneurCasPossible.end(); var2++)
        {
            if (var1->second[0] < var2->second[0] && var1->second[1] < var2->second[1])
            {
                svgout.addDisk(var2->second[0]*10,600-var2->second[1],5,"red");
                conteneurCasPossible.erase(var2);
            }
        }
    }
    std::cout << conteneurCasPossible.size() << std::endl;
    for (var1 = conteneurCasPossible.begin(); var1 != conteneurCasPossible.end(); var1++)
    {
        svgout.addDisk(var1->second[0]*10,600-var1->second[1],5,"green");
    }
}

float graphe::Dijkstra(int idSommet , std::vector<std::string> casActuel)
{
    std::vector<float> Distances(m_sommets.size());
    float recuppoids=0;
    float distanceTotale=0;
    for(float i=0;i<m_sommets.size();i++)
        Distances[i]=10000000.0;
    Distances[idSommet] = 0;
    std::unordered_set< std::string > marquage;
    std::priority_queue< std::pair <std::string,float>, std::vector< std::pair <std::string,float> >, prioritize > file;
    file.push(make_pair(std::to_string(idSommet),0));
    while(!file.empty())
    {
        std::pair<std::string, float> curr = file.top();
        marquage.insert({curr.first});
        file.pop();
        std::string v = curr.first;
        float w = curr.second;
        for (int i = 0; i < m_sommets.find(curr.first)->second->getVoisins().size(); ++i)
        {
            recuppoids=0;
            Sommet* it = m_sommets.find(curr.first)->second->getVoisins()[i];
            //std::cout<<m_sommets.find(curr.first)->second->getVoisins().size();
            std::unordered_set<std::string>::const_iterator got = marquage.find (it->getId());
            if (got == marquage.end())
            {
                for (int j=0; j < casActuel.size(); ++j)
                {
                    std::string sommetDepart = m_aretes.find(casActuel[j])->second->getSommetDepart();
                    std::string sommetArrive = m_aretes.find(casActuel[j])->second->getSommetArrive();
                    std::string sommetDepart2 = m_aretes.find(casActuel[j])->second->getSommetArrive();
                    std::string sommetArrive2 = m_aretes.find(casActuel[j])->second->getSommetDepart();
                    if ((sommetDepart == curr.first && sommetArrive == it->getId()) || (sommetDepart2 == curr.first && sommetArrive2 == it->getId()))
                    {
                        recuppoids = m_aretes.find(casActuel[j])->second->getPoids2();
                        if ( w + recuppoids < Distances[std::stof(it->getId())])
                        {
                            //std::cout<<w<<std::endl;
                            Distances[std::stof(it->getId())] =  w + recuppoids ;
                            file.push(make_pair(it->getId(),Distances[std::stof(it->getId())]));
                            distanceTotale += Distances[std::stof(it->getId())];
                            //printf("_%f_",Distances[std::stof(it->getId())]);
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
