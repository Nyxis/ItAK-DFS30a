#ifndef RESULT_H
#define RESULT_H

#include <string>
#include "ResultType.h"

namespace rpg {

class Result {
private:
    int value;
    int percent;
    ResultType type;

public:
    Result(int value, int percent, ResultType type);
    ~Result() = default;

    int getValue() const;
    int getPercent() const;
    ResultType getType() const;
    std::string toString() const;
};

}

#endif