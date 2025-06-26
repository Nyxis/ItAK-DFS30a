#include "Lib/PercentInt.h"
#include <stdexcept>

PercentInt::PercentInt(int value) : value(value) {
    if (value < 0 || value > 100) {
        throw std::out_of_range("PercentInt value must be between 0 and 100.");
    }
}
