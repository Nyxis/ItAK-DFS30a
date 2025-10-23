#ifndef SCENARIO_HPP
#define SCENARIO_HPP

#include <string>
#include <vector>
#include "Encounter.hpp"

class Scenario {
private:
    std::string nom;
    std::vector<Encounter> rencontres;

public:
    Scenario(const std::string& nom);

    void ajouterEncounter(const Encounter& e);
    const std::vector<Encounter>& getRencontres() const;
    std::string getNom() const;
};

#endif
