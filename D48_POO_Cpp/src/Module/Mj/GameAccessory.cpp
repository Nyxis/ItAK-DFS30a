#include "Lib/PercentInt.h"
#include "Lib/Randomizer.h"
#include "Module/Mj/GameAccessory.h"
#include <iostream> // For std::ostream

namespace Jdr::Mj {

    GameAccessory::GameAccessory() : randomizer(Randomizer())
    {}

    PercentInt GameAccessory::getScore() const {
        return PercentInt(this->score);
    }
    
    /**
     * Surcharge l'opérateur "<<" pour afficher les informations de l'accessoire.
     * Équivalent d'un __toString() en Php.
     */
    std::ostream& operator<<(std::ostream& os, const GameAccessory& g) {
        os << g.value << "(" << g.score << "%)";
        
        return os;
    }

} // namespace Jdr::Mj
