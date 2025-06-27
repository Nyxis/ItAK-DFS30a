#include "Result.h"

namespace rpg {

Result::Result( int percent, ResultType type)
    : percent(percent), type(type) {}

int Result::getPercent() const {
    return percent;
}



ResultType Result::getType() const {
    return type;
}

std::string Result::toString() const {
    switch (type) {
        case ResultType::FUMBLE: return "Fumble";
        case ResultType::FAILURE: return "Failure";
        case ResultType::SUCCESS: return "Success";
        case ResultType::CRITICAL_SUCCESS: return "Critical Success";
        default: return "Unknown";
    }
}

}
