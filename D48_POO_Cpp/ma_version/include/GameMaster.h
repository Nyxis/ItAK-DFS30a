#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <vector>
#include <memory>
#include "RandomGenerator.h"
#include "Scenario.h"
#include "Adventurer.h"

namespace rpg {

class GameMaster {
private:
    std::vector<std::shared_ptr<RandomGenerator>> gameAccessories;
    std::vector<std::shared_ptr<Adventurer>> adventurers;

    
    void setupDefaultAccessories();
    
    public:
    GameMaster();
    ~GameMaster() = default;
    
    void addAccessory(const std::shared_ptr<RandomGenerator>& accessory);
    bool hasAccessories() const;
    void clearAccessories();
    
    void registerAdventurer(const std::shared_ptr<Adventurer>& adventurer);
    void playScenario(const Scenario& scenario);
};

}

#endif
