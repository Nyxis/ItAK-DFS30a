#pragma once
#include <random>
#include <vector>
#include <stdexcept>

class Randomizer
{
    public:
        Randomizer();
        ~Randomizer() = default;
        int rand(int min, int max) const;
        int rand(int max) const;

        template<typename T>
        int rand(const std::vector<T>& vec) const {
            if (vec.empty()) {
                throw std::invalid_argument("Cannot select a random element from an empty vector.");
            }
            
            return this->rand(0, static_cast<int>(vec.size() - 1));
        }
        
    private:
        mutable std::mt19937 gen;   // pour autoriser même dans les méthodes const
};
