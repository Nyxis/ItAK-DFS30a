#pragma once
#include "Lib/PercentInt.h"
#include "Lib/Randomizer.h"
#include <iostream>

namespace Jdr::Mj {
    class GameAccessory {
        public:
            GameAccessory();
            virtual ~GameAccessory() = default;

            virtual GameAccessory* activate() = 0;

            PercentInt getScore() const;

            friend std::ostream& operator<<(std::ostream& os, const GameAccessory& g);
        
        protected:
            int value;
            int score;
            Randomizer randomizer;
    };
}
