#pragma once
#include <string>
#include "Module/Encounter/Outcome.h"

namespace Jdr::Encounter {
    struct Result
    {
        Result(Outcome outcome, int percentScore);
        ~Result() = default ;

        const Outcome outcome;
        const int percentScore;
    };    
}
