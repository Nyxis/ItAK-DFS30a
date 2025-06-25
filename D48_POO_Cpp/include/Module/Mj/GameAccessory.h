#pragma once
#include <random>
#include <iostream>

namespace Jdr::Mj {
    class GameAccessory {
        public:
            GameAccessory();
            virtual ~GameAccessory() = default;

            virtual GameAccessory* activate() = 0;

            friend std::ostream& operator<<(std::ostream& os, const GameAccessory& g);
        
        protected:
            int value;
            int score;
            int rand(int min, int max);

        private:
            std::mt19937 gen;
    };


}
