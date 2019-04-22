#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"
#include "arete.h"

Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
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

int Sommet::getId() const {
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

Sommet::~Sommet()
{

}
