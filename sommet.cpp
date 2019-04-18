#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"
#include "arete.h"

Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin(Sommet* voisin){
    m_voisins.push_back(voisin);
}
 void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
 }
void Sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins) {
        v->afficherData();
    }
}

std::string Sommet::getId() const {
    return m_id;
}

int Sommet::getDegre() const{
    int degre=0;
    for (auto s: m_voisins) /// Pour chaque voisin on incremente la valeur de degre
    {
        degre++;
    }
    return degre;
}

int Sommet::getX() const{
    return m_x;
}

int Sommet::getY() const{
    return m_y;
}

std::vector<Sommet*> Sommet::getVoisins(){
    return m_voisins;
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const{
    Sommet*sommetpremier=new Sommet(m_id,m_x,m_y); /// on cr�� un sommet qui prend les valeurs de l'appelant
    sommetpremier->m_voisins=m_voisins;
    std::unordered_map<std::string,std::string> l_pred;
    std::unordered_set<std::string> marquage;
    marquage.insert(m_id);
    std::queue<Sommet*> file; ///on cr�� une file de sommmet
    file.push(sommetpremier);       /// on ajoute le sommet � la file
    while(!file.empty()) /// tant que la fille n'est pas vide
    {
        Sommet*sommetactuel=file.front();
        marquage.insert({sommetactuel->m_id});
        file.pop(); /// on supprime le premier �l�ment de la file
        for (Sommet* it : sommetactuel->m_voisins) /// Parcours de tous les voisins
        {
            std::unordered_set<std::string>::const_iterator got = marquage.find (it->m_id);
            if (got == marquage.end())  /// Si le sommet voisin n'est pas marqu�
            {
                file.push(it);          /// on l'ajoute � la file
                l_pred.insert({it->m_id,sommetactuel->m_id});    /// on le place dans l'unordered map
            }
        }
    }
    delete sommetpremier; /// lib�re la m�moire
    return l_pred;
}

std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const{
    Sommet*sommetpremier=new Sommet(m_id,m_x,m_y); /// M�me principe que le parcours BFS
    sommetpremier->m_voisins=m_voisins;
    std::unordered_map<std::string,std::string> l_pred;
    std::unordered_set<std::string> marquage;
    marquage.insert(m_id);
    std::stack<Sommet*> pile;  /// Cr�ation d'une pile
    pile.push(sommetpremier);
    while(!pile.empty())
    {
        Sommet*sommetactuel=pile.top();
        marquage.insert({sommetactuel->m_id});
        pile.pop();
        for (Sommet* it : sommetactuel->m_voisins)
        {
            std::unordered_set<std::string>::const_iterator got = marquage.find (it->m_id);
            if (got == marquage.end())  /// si le sommet est non marqu�
            {
                pile.push(it);
                l_pred.insert({it->m_id,sommetactuel->m_id});
            }
        }
    }
    delete sommetpremier;
    return l_pred;
}
std::unordered_set<std::string> Sommet::rechercherCC() const{
    std::unordered_set<std::string> cc;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=parcoursBFS();
    for(auto s:l_pred) ///parcours de l'unordered map r�cup�r�e du parcours BFS
        {
            cc.insert(s.first); ///premier element
            std::pair<std::string,std::string> pred=s;
            while(pred.second!=m_id) /// tous les suivants
            {
                pred=*l_pred.find(pred.second);
                cc.insert(pred.first);
            }
            cc.insert(m_id); ///sommet de d�part
        }
    if (l_pred.size()==0) /// si le sommet de d�part n'a pas de voisin
    {
        cc.insert(m_id);
    }
    return cc;
}
Sommet::~Sommet()
{
    //dtor
}
