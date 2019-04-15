#ifndef ARETE_H
#define ARETE_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Arete
{
    public:
        Arete(std::string id, std::string sommet_depart, std::string sommet_arrive);
        void ajouterPoids(float poids);
        std::vector<float>getPoids()const;
        std::string getSommetDepart() const;
        std::string getSommetArrive() const;
        virtual ~Arete();

    private:
        std::string m_id;
        std::vector<float> m_poids;
        std::string m_sommet_depart;
        std::string m_sommet_arrive;
};

#endif // ARETE_H
