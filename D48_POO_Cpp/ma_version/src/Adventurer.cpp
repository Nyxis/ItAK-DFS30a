#include "Adventurer.h"
#include <iostream>

namespace rpg {

Adventurer::Adventurer(const std::string& name, int level, int maxHp)
    : name(name), level(level), maxHp(maxHp), currentHp(maxHp) {}

const std::string& Adventurer::getName() const {
    return name;
}

int Adventurer::getLevel() const {
    return level;
}

int Adventurer::getMaxHp() const {
    return maxHp;
}

int Adventurer::getCurrentHp() const {
    return currentHp;
}

void Adventurer::takeDamage(int dmg) {
    currentHp -= dmg;
    if (currentHp < 0) currentHp = 0;
    std::cout << name << " a subi " << dmg << " dégâts. PV restants : " << currentHp << std::endl;
}

void Adventurer::heal(int amount) {
    currentHp += amount;
    if (currentHp > maxHp) currentHp = maxHp;
    std::cout << name << " récupère " << amount << " PV. PV actuels : " << currentHp << std::endl;
}

void Adventurer::levelUp() {
    level++;
    std::cout << name << " passe au niveau " << level << " !" << std::endl;
}

void Adventurer::kill() {
    currentHp = 0;
    std::cout << name << " est mort..." << std::endl;
}

bool Adventurer::isDead() const {
    return currentHp <= 0;
}

}
