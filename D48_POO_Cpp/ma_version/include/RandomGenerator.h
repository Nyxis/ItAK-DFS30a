#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include "Result.h"

namespace rpg {

class RandomGenerator {
public:
    virtual ~RandomGenerator() = default;

    virtual int generate() = 0;

    virtual int getMax() const = 0;

};

} 

#endif
