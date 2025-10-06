#include "GameMaster.h"
#include "Dice.h"
#include "Coin.h"
#include "Deck.h"
#include <iostream>
#include <random>
#include <chrono>

namespace rpg {

GameMaster::GameMaster() {}

void GameMaster::setupDefaultAccessories() {
    gameAccessories.push_back(std::make_shared<Dice>(6));
    gameAccessories.push_back(std::make_shared<Dice>(10));
    gameAccessories.push_back(std::make_shared<Dice>(20));

    gameAccessories.push_back(std::make_shared<Coin>(3));
    gameAccessories.push_back(std::make_shared<Coin>(5));

    gameAccessories.push_back(std::make_shared<Deck>(3, 18));
    gameAccessories.push_back(std::make_shared<Deck>(4, 13));
}

void GameMaster::addAccessory(const std::shared_ptr<RandomGenerator>& accessory) {
    gameAccessories.push_back(accessory);
}

bool GameMaster::hasAccessories() const {
    return !gameAccessories.empty();
}

void GameMaster::clearAccessories() {
    gameAccessories.clear();
}

void GameMaster::registerAdventurer(const std::shared_ptr<Adventurer>& adventurer) {
    adventurers.push_back(adventurer);
}

void GameMaster::playScenario(const Scenario& scenario) {
    if (adventurers.empty()) {
        std::cerr << "[INFO] Aucun aventurier enregistré. Ajoutez-en avec registerAdventurer(name, level, maxHp) \n";
        return;
    }

    if (gameAccessories.empty()) {
        std::cout << "[INFO] Aucun accessoire défini, chargement des accessoires par défaut.\n";
        setupDefaultAccessories();
    }

    std::cout << "\n--- Début du scénario : " << scenario.getName() << " ---\n";

    for (const auto& encounter : scenario.getEncounters()) {
        std::cout << "\nRencontre : " << encounter->getTitle() << "\n";
        std::cout << encounter->getDescription() << "\n";

        for (const auto& adventurer : adventurers) {
            
            static std::mt19937 rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
            std::uniform_int_distribution<int> dist(0, static_cast<int>(gameAccessories.size()) - 1);
            int index = dist(rng);

            std::cout << "\n--------------------\n" << "\n" << adventurer->getName() << " joue : \n";

            int value = gameAccessories[index]->generate();
            int max = gameAccessories[index]->getMax();

            Result result = encounter->resolve(value, max);
            std::cout << '\n' << adventurer->getName() << " obtient : "
                      << result.getPercent() << "% (" << result.toString() << ")\n" << "\n--------------------\n" ;

            
        }
    }

    std::cout << "\n--- Fin du scénario ---\n";
}

}