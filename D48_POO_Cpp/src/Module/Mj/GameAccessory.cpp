#include "Module/Mj/GameAccessory.h"
#include "Module/Encounter/Result.h"
#include "Module/Encounter/Outcome.h"
#include "Lib/PercentInt.h" 
#include <iostream> // For std::ostream

using namespace Jdr::Encounter;

namespace Jdr::Mj {

    GameAccessory::GameAccessory() 
        : gen(std::random_device{}()) // Initialize the random number generator with a random seed
    {}

    int GameAccessory::rand(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);

        return dist(this->gen); // Generates a random number between min and max (inclusive)
    }

    Encounter::Result GameAccessory::getResult() const {
        Encounter::Outcome outcome;

        if (this->score == 0) outcome = Encounter::Outcome::Fumble;
        else if (this->score == 100) outcome = Encounter::Outcome::Critical;
        else if (this->score >= 50) outcome = Encounter::Outcome::Success;
        else outcome = Encounter::Outcome::Failure;
        
        return Result(outcome, PercentInt(this->score));
    }

    /**
     * Surcharge l'opérateur "<<" pour afficher les informations de l'accessoire.
     * Équivalent d'un __toString() en Php.
     */
    std::ostream& operator<<(std::ostream& os, const GameAccessory& g) {
        auto result = g.getResult();

        os << g.value << " > " << result.outcome << " (" << result.percentScore.value << "%)";
        
        return os;
    }

} // namespace Jdr::Mj
