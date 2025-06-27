#ifndef SCENARIO_H
#define SCENARIO_H

#include <string>
#include <vector>
#include <memory>
#include "Encounter.h"

namespace rpg {

class Scenario {
private:
    std::string name;
    std::vector<std::shared_ptr<Encounter>> encounters;

public:
    Scenario(const std::string& name);
    ~Scenario() = default;

    void addEncounter(std::shared_ptr<Encounter> encounter);
    const std::string& getName() const;
    const std::vector<std::shared_ptr<Encounter>>& getEncounters() const;
};

}

#endif
