#include "arete.h"

Arete::Arete(std::string id, std::string sommet_depart, std::string sommet_arrive): m_id{id},m_sommet_depart{sommet_depart},m_sommet_arrive{sommet_arrive}
{
}

void Arete::ajouterPoids(float poids){
    m_poids.push_back(poids);
}
std::vector<float> Arete::getPoids()const{
    return m_poids;
}
Arete::~Arete()
{
    //dtor
}

