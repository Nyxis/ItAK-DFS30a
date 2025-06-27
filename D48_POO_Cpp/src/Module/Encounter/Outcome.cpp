#include "Module/Encounter/Outcome.h"
#include <iostream>
#include <string>

namespace Jdr::Encounter {

    std::ostream& operator<<(std::ostream& os, const Outcome& o) {
        switch (o) {
            case Outcome::Fumble:   return os << "💀fumble";
            case Outcome::Failure:  return os << "💥échec";
            case Outcome::Success:  return os << "✨succès";
            case Outcome::Critical: return os << "⚡critique";
            default:                return os << "Inconnu";
        }
    }

} // namespace Jdr::Encounter
