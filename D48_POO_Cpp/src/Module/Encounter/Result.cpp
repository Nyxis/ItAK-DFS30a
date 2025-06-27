#include "Module/Encounter/Result.h"
#include "Lib/PercentInt.h"
#include <iostream>

namespace Jdr::Encounter {

    Result::Result(Outcome outcome, PercentInt percentScore)
        : outcome(outcome), percentScore(percentScore)
        {}   

    /**
     * Surcharge l'opérateur "<<" pour afficher les informations de l'accessoire.
     * Équivalent d'un __toString() en Php.
     */
    std::ostream& operator<<(std::ostream& os, const Result& r) {
        os << r.outcome << " (" << r.percentScore.value << "%)";
        
        return os;
    }

} // namespace Jdr::Encounter   
