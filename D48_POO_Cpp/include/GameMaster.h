#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <vector>
#include <memory>
#include "RandomGenerator.h"
#include "Result.h"

namespace rpg {

class GameMaster {
private:
    std::vector<std::shared_ptr<RandomGenerator>> gameAccessories;

    void setupGameAccessories();
    ResultType evaluate(int percent) const;

public:
    GameMaster();
    ~GameMaster() = default;

    Result pleaseGiveMeACrit();
};

}

#endif
