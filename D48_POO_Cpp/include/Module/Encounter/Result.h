#pragma once
#include <string>
#include <iostream>
#include "Module/Encounter/Outcome.h"
#include "Lib/PercentInt.h"

namespace Jdr::Encounter {
    struct Result
    {
        Result(Outcome outcome, PercentInt percentScore);
        ~Result() = default ;

        const Outcome outcome;
        const PercentInt percentScore;
        
    };    
    
    std::ostream& operator<<(std::ostream& os, const Result& r);
}
