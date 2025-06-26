#include "GameMaster.h"
#include "Dice.h"
#include "Coin.h"
#include "Deck.h"
#include <random>
#include <chrono>
#include <iostream>

namespace rpg {

GameMaster::GameMaster() {
    setupGameAccessories();
}

void GameMaster::setupGameAccessories() {
    gameAccessories.push_back(std::make_shared<Dice>(6));
    gameAccessories.push_back(std::make_shared<Dice>(10));
    gameAccessories.push_back(std::make_shared<Dice>(20));

    gameAccessories.push_back(std::make_shared<Coin>(3));
    gameAccessories.push_back(std::make_shared<Coin>(3));

    gameAccessories.push_back(std::make_shared<Deck>(3, 18));
    gameAccessories.push_back(std::make_shared<Deck>(4, 13));
}

ResultType GameMaster::evaluate(int percent) const {
    if (percent == 0)
        return ResultType::FUMBLE;
    if (percent == 100)
        return ResultType::CRITICAL_SUCCESS;
    if (percent < 50)
        return ResultType::FAILURE;
    return ResultType::SUCCESS;
}

Result GameMaster::pleaseGiveMeACrit() {
    if (gameAccessories.empty()) {
        std::cerr << "Erreur : aucun accessoire disponible !" << std::endl;
        return Result(0, 0, ResultType::FAILURE);
    }

    static std::mt19937 rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, static_cast<int>(gameAccessories.size()) - 1);
    int index = dist(rng);

    int value = gameAccessories[index]->generate();
    int max = gameAccessories[index]->getMax();

    int percent = (value * 100) / max;
    ResultType type = evaluate(percent);

    return Result(value, percent, type);
}

}
