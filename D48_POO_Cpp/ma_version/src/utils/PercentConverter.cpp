#include "utils/PercentConverter.h"

namespace rpg::utils {

    int PercentConverter::fromRawValue(int value, int max) {
        if (max <= 0) return 0;
        return (value * 100) / max;
    }


}
