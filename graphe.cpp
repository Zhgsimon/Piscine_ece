#include <fstream>
#include <iostream>
#include "graphe.h"

graphe::graphe(std::string nomFichier,std::string fichierPoids){
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_depart;
    std::string id_arrive;
    std::string id_arete;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extr�mit�s
        ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture poids arete");
        ifs>>id_depart; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_arrive; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        m_aretes.insert({id_arete,new Arete{id_arete,id_depart,id_arrive}});
        (m_sommets.find(id_depart))->second->ajouterVoisin((m_sommets.find(id_arrive))->second);
        (m_sommets.find(id_arrive))->second->ajouterVoisin((m_sommets.find(id_depart))->second);
    }
    ifs.close();
    std::ifstream ifs2{fichierPoids};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
}
void graphe::afficher() const{
    int numero=0;
    int nbsommet=0;
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"Ordre : "<<m_sommets.size()<<std::endl;
    while ( nbsommet != m_sommets.size()) /// Tant qu'on a pas trouv� le m�me nombre de sommet que le graphe comporte
    {
        if(m_sommets.find(std::to_string(numero))!=m_sommets.end()) /// si le sommet existe
        {
            Sommet*s0=(m_sommets.find(std::to_string(numero)))->second; ///r�cupation des valeurs puis affichage
            s0->afficherData();
            s0->afficherVoisins();
            nbsommet++;
        }
        numero++;
        std::cout<<std::endl;
    }
}

void graphe::parcoursBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}
void graphe::afficherBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
int graphe::rechercher_afficherToutesCC() const{
    int i=0;
    int compteursommet=0;
    int nbsommet=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set<std::string> recup;
    std::unordered_set<std::string> save;
    while (nbsommet != m_sommets.size())
    {
        if (save.find(std::to_string(compteursommet))==save.end()) /// si le sommet est non marqu�
        {
            i++;
            Sommet*s0=(m_sommets.find(std::to_string(compteursommet)))->second;
            recup=s0->rechercherCC();  ///on r�cup�re une composante connexe
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
        else compteursommet++;
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
    if (degreimpair == 0) /// cycle eul�rien
        return 2;
    if (degreimpair ==2)  /// chaine eul�rienne
    {
        std::vector<std::string> :: iterator itr;
        std::cout <<"Les extremites sont : ";
        for (itr = liste_impair.begin(); itr != liste_impair.end(); itr++) /// affichage des extr�mit�s
        {
           std::cout <<(*itr) <<"    ";
        }
        return 1;
    }
    if (degreimpair!=0 && degreimpair!=2) /// rien d'eulerien
        return 0;
}

graphe::~graphe()
{
    //dtor
}
