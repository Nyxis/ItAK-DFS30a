#include "Module/Encounter/Result.h"

namespace Jdr::Encounter {

    Result::Result(Outcome outcome, int percentScore)
        : outcome(outcome), percentScore(percentScore)
        {}   

} // namespace Jdr::Encounter   
