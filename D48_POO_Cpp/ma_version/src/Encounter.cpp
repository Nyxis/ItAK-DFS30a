#include "Encounter.h"
#include "utils/PercentConverter.h"

namespace rpg {

Encounter::Encounter(const std::string& title,
                     const std::string& description,
                     int fumbleThreshold,
                     int failureThreshold,
                     int successThreshold,
                     int criticalSuccessThreshold)
    : title(title),
      description(description),
      fumbleThreshold(fumbleThreshold),
      failureThreshold(failureThreshold),
      successThreshold(successThreshold),
      criticalSuccessThreshold(criticalSuccessThreshold) {}

const std::string& Encounter::getTitle() const {
    return title;
}

const std::string& Encounter::getDescription() const {
    return description;
}

Result Encounter::resolve(int rawValue, int maxValue) const {
    int percent = utils::PercentConverter::fromRawValue(rawValue, maxValue);
    return play(percent);
}

Result Encounter::play(int percent) const {
    ResultType type;

    if (percent <= fumbleThreshold) {
        type = ResultType::FUMBLE;
    } else if (percent <= failureThreshold) {
        type = ResultType::FAILURE;
    } else if (percent <= successThreshold) {
        type = ResultType::SUCCESS;
    } else {
        type = ResultType::CRITICAL_SUCCESS;
    }

    return Result(percent, type);
}

} 
