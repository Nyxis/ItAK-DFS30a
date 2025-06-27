#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <string>
#include "Result.h"

namespace rpg {

class Encounter {
private:
    std::string title;
    std::string description;

    int fumbleThreshold;
    int failureThreshold;
    int successThreshold;
    int criticalSuccessThreshold;

    Result play(int percent) const;


public:
    Encounter(const std::string& title,
              const std::string& description,
              int fumbleThreshold,
              int failureThreshold,
              int successThreshold,
              int criticalSuccessThreshold);

    ~Encounter() = default;

    const std::string& getTitle() const;
    const std::string& getDescription() const;

    Result resolve(int rawValue, int maxValue) const;
};

}

#endif
