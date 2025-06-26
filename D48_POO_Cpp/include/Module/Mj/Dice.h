#pragma once
#include "GameAccessory.h"

namespace Jdr::Mj {
    class Dice : public GameAccessory
    {
        public:
            Dice(int nbFaces);
            ~Dice() = default;

            Dice* roll();

            /**
             * Activate the die, roll it and set its value and score.
             */
            virtual GameAccessory* activate() override;

            const int nbFaces;
    };
};
