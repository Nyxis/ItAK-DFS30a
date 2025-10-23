#ifndef ENCOUNTER_HPP
#define ENCOUNTER_HPP

#include <string>
#include "ResultatTirage.hpp"

class Encounter {
private:
    std::string titre;
    std::string description;

    int seuilFumble;
    int seuilEchec;
    int seuilReussite;
    int seuilCritique;

public:
    Encounter(const std::string& titre, const std::string& description,
              int seuilFumble, int seuilEchec, int seuilReussite, int seuilCritique);

    std::string getTitre() const;
    std::string getDescription() const;

    std::string evaluer(int pourcentage) const;
};

#endif
