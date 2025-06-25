#include "Module/Mj/GameAccessory.h"
#include <iostream> // For std::ostream

namespace Jdr::Mj {

    GameAccessory::GameAccessory() 
        : gen(std::random_device{}()) // Initialize the random number generator with a random seed
    {}

    int GameAccessory::rand(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);

        return dist(this->gen); // Generates a random number between min and max (inclusive)
    }

    /**
     * Surcharge l'opérateur "<<" pour afficher les informations de l'accessoire.
     * Équivalent d'un __toString() en Php.
     */
    std::ostream& operator<<(std::ostream& os, const GameAccessory& g) {
        os << g.value << " (" << g.score << "%)";
        
        return os;
    }

} // namespace Jdr::Mj
