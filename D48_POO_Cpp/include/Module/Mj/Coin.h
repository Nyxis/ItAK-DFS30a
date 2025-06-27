#pragma once
#include "GameAccessory.h"
#include <vector>

namespace Jdr::Mj {
    class Coin : public GameAccessory
    {
        public:
            Coin(int nbFlips = 1);
            ~Coin() = default ;

            /**
             * Flips the coin a specified number of times.
             */
            Coin* flip();

            /**
             * Activates the coin, performing the flip and calculating the score.
             */
            virtual GameAccessory* activate() override;

        private:
            int nbFlips;
            std::vector<int> scoreLadder;

            int flipUntilFailureOrMaxFlips(int currentFlip);
    };
};
