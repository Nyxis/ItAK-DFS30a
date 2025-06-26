#include "Module/Encounter/Result.h"
#include "Lib/PercentInt.h"

namespace Jdr::Encounter {

    Result::Result(Outcome outcome, PercentInt percentScore)
        : outcome(outcome), percentScore(percentScore)
        {}   

} // namespace Jdr::Encounter   
