#include "Module/Mj/Dice.h"
#include "Module/Mj/GameAccessory.h"
#include <cmath>        /* round / ceil / floor */

namespace Jdr::Mj {
    Dice::Dice(int nbFaces) : nbFaces(nbFaces) 
    {}

    Dice* Dice::roll()
    {
        this->value = this->randomizer.rand(1, this->nbFaces);
        this->score = std::round(static_cast<double>(this->value) / this->nbFaces * 100.0);

        return this;
    }

    GameAccessory* Dice::activate()
    {
        return this->roll();
    }
}
