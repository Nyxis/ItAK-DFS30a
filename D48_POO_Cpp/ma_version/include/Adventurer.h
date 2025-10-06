#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <string>

namespace rpg {

class Adventurer {
private:
    std::string name;
    int level;
    int maxHp;
    int currentHp;

public:
    Adventurer(const std::string& name, int level, int maxHp);
    ~Adventurer() = default;

    const std::string& getName() const;
    int getLevel() const;
    int getMaxHp() const;
    int getCurrentHp() const;

    void takeDamage(int dmg);
    void heal(int amount);
    void levelUp();
    void kill();
    bool isDead() const;
};

}

#endif
