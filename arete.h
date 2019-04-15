#ifndef ARETE_H
#define ARETE_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Arete
{
    public:
        Arete(std::string id, std::string sommet_depart, std::string sommet_arrive, float couts=0, float temps=0);
        virtual ~Arete();

    private:
        std::string m_id;
        float m_couts;
        float m_temps;
        std::string m_sommet_depart;
        std::string m_sommet_arrive;
};

#endif // ARETE_H
