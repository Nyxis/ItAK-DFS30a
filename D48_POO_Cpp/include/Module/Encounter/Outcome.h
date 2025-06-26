#pragma once
#include <string>

namespace Jdr::Encounter
{
    // Enum class to represent the possible outcomes of an encounter
    // Success: The encounter was successful.
    // Failure: The encounter failed, but it wasn't catastrophic.
    // Critical: The encounter had a significant positive outcome.
    // Fumble: The encounter resulted in a disastrous failure.
    enum class Outcome { Success, Failure, Critical, Fumble };

    std::ostream& operator<<(std::ostream& os, const Outcome& o);
}
