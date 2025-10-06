#ifndef DECK_H
#define DECK_H

#include "RandomGenerator.h"
#include <random>

namespace rpg {

class Deck : public RandomGenerator {
private:
    int colors;
    int values;

    std::mt19937 rng;
    std::uniform_int_distribution<int> colorDist;
    std::uniform_int_distribution<int> valueDist;

public:
    Deck(int colors, int values);
    ~Deck() = default;

    int generate() override;
    int getMax() const override;

};

} // namespace rpg

#endif
