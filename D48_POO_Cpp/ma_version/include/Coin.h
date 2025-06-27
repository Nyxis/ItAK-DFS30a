#ifndef COIN_H
#define COIN_H

#include "RandomGenerator.h"
#include <random>

namespace rpg {

class Coin : public RandomGenerator {
private:
    int flips;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

    int flipRecursive(int remaining);

public:
    Coin(int flips);
    ~Coin() = default;

    int generate() override;
    int getMax() const override;

};

}

#endif
