#include "Dice.h"
#include <chrono>
#include <iostream>

namespace rpg {

Dice::Dice(int faces)
    : faces(faces),
      rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())),
      dist(1, faces) {}

int Dice::generate() {
    int resultValue = dist(rng);
    std::cout << "Valeur tirée : " << resultValue << " sur un dé à " << faces << " faces" << std::endl;
    return resultValue;
}

int Dice::getMax() const {
    return faces;

}

}
