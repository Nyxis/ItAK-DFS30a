#ifndef DICE_H
#define DICE_H

#include "RandomGenerator.h"
#include <random>

namespace rpg {

class Dice : public RandomGenerator {
private:
    int faces;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

public:
    Dice(int faces);
    ~Dice() = default;

    int generate() override;
    int getMax() const override;
};

}

#endif
