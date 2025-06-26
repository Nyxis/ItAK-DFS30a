#pragma once
#include "Module/Encounter/Result.h"
#include <random>
#include <iostream>

using Jdr::Encounter::Result;

namespace Jdr::Mj {
    class GameAccessory {
        public:
            GameAccessory();
            virtual ~GameAccessory() = default;

            virtual GameAccessory* activate() = 0;

            Result getResult() const;

            friend std::ostream& operator<<(std::ostream& os, const GameAccessory& g);
        
        protected:
            int value;
            int score;
            int rand(int min, int max);

        private:
            std::mt19937 gen;
    };
}
