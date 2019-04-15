#include "arete.h"

Arete::Arete(std::string id, std::string sommet_depart, std::string sommet_arrive, float couts, float temps): m_id{id},m_sommet_depart{sommet_depart},m_sommet_arrive{sommet_arrive},m_couts{couts},m_temps{temps}
{
}

Arete::~Arete()
{
    //dtor
}

