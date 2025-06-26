#include "Result.h"

namespace rpg {

Result::Result(int value, int percent, ResultType type)
    : value(value), percent(percent), type(type) {}

int Result::getPercent() const {
    return percent;
}

int Result::getValue() const {
    return value;
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
