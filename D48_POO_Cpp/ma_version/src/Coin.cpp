#include "Coin.h"
#include <chrono>
#include <iostream>

namespace rpg {

Coin::Coin(int flips)
    : flips(flips),
      rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())),
      dist(0, 1) {}

int Coin::flipRecursive(int remaining) {
    if (remaining == 0) return 0;

    int tirage = dist(rng);
    std::string resultat = (tirage == 1) ? "Pile" : "Face";
    std::cout << "Lancer " << flips - remaining + 1 << " : " << resultat << std::endl;

    return tirage + flipRecursive(remaining - 1);
}

int Coin::generate() {
    return flipRecursive(flips);
}

int Coin::getMax() const {
    return flips;
}


}
