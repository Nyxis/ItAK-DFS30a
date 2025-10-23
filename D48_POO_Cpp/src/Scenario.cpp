#include "Scenario.hpp"

Scenario::Scenario(const std::string& nom) : nom(nom) {}

void Scenario::ajouterEncounter(const Encounter& e) {
    rencontres.push_back(e);
}

const std::vector<Encounter>& Scenario::getRencontres() const {
    return rencontres;
}

std::string Scenario::getNom() const {
    return nom;
}
