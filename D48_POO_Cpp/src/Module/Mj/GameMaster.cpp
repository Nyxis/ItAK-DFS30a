#include "Module/Mj/GameMaster.h"
#include "Module/Encounter/Result.h"
#include "Lib/Randomizer.h"
#include <vector>

using namespace Jdr::Encounter;

namespace Jdr::Mj {

    GameMaster::GameMaster(std::vector<GameAccessory*> accessories)
        : accessories(std::move(accessories)), randomizer(Randomizer())
    {
        if (this->accessories.empty()) {
            throw std::invalid_argument("GameMaster requires at least one GameAccessory.");
        }
    }

    Result GameMaster::generateResult(PercentInt score) const
    {
        Encounter::Outcome outcome;

        if (score.value == 0) outcome = Encounter::Outcome::Fumble;
        else if (score.value == 100) outcome = Encounter::Outcome::Critical;
        else if (score.value >= 50) outcome = Encounter::Outcome::Success;
        else outcome = Encounter::Outcome::Failure;
        
        return Result(outcome, score);
    }

    Result GameMaster::pleaseGiveMeACrit() const 
    {
        return this->generateResult(
            this->accessories[this->randomizer.rand(this->accessories)]
                ->activate()
                ->getScore()
        );
    }

} // namespace Jdr::Mj
