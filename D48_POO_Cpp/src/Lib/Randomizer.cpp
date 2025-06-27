#include "Lib/Randomizer.h"
#include <random>

Randomizer::Randomizer() : gen(std::random_device{}())
{};

int Randomizer::rand(int min, int max) const
{
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

int Randomizer::rand(int max) const
{
    return rand(0, max);
}
