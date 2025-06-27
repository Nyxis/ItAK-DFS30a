#pragma once
#include "Module/Mj/GameAccessory.h"
#include "Module/Encounter/Result.h"
#include "Lib/PercentInt.h"

using namespace Jdr::Encounter;

namespace Jdr::Mj {
    class GameMaster {
        public:
            GameMaster(std::vector<GameAccessory*> accessories);
            ~GameMaster() = default;

            Result pleaseGiveMeACrit() const;

            Result generateResult(PercentInt score) const;

        private:
            const std::vector<GameAccessory*> accessories;
            const Randomizer randomizer;
    };
}
