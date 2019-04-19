#include "arete.h"

Arete::Arete(int id, int sommet_depart, int sommet_arrive): m_id{id},m_sommet_depart{sommet_depart},m_sommet_arrive{sommet_arrive}
{
}

void Arete::ajouterPoids(float poids){
    m_poids.push_back(poids);
}

float Arete::getPoids()const{
    return m_poids[0];
}

float Arete::getPoids2()const{
    return m_poids[1];
}

int Arete::getSommetDepart() const{
    return m_sommet_depart;
}

int Arete::getSommetArrive() const{
    return m_sommet_arrive;
}

int Arete::getId() const {
    return m_id;
}

Arete::~Arete()
{
    //dtor
}

