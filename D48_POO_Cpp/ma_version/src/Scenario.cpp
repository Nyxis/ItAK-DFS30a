#include "Scenario.h"

namespace rpg {

Scenario::Scenario(const std::string& name) : name(name) {}

void Scenario::addEncounter(std::shared_ptr<Encounter> encounter) {
    encounters.push_back(encounter);
}

const std::string& Scenario::getName() const {
    return name;
}

const std::vector<std::shared_ptr<Encounter>>& Scenario::getEncounters() const {
    return encounters;
}

}