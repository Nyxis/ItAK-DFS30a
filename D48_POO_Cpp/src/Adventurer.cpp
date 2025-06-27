#include "Adventurer.hpp"

Adventurer::Adventurer(const std::string& nom, int niveau, int pvMax)
    : nom(nom), niveau(niveau), pvMax(pvMax), pvActuels(pvMax) {}

std::string Adventurer::getNom() const {
    return nom;
}

int Adventurer::getNiveau() const {
    return niveau;
}

int Adventurer::getPV() const {
    return pvActuels;
}

int Adventurer::getPVMax() const {
    return pvMax;
}

void Adventurer::blesser(int points) {
    pvActuels -= points;
    if (pvActuels < 0)
        pvActuels = 0;
}

void Adventurer::soigner(int points) {
    pvActuels += points;
    if (pvActuels > pvMax)
        pvActuels = pvMax;
}

void Adventurer::tuer() {
    pvActuels = 0;
}

void Adventurer::monterNiveau() {
    niveau++;
    pvMax += 10;
    pvActuels = pvMax;
}
