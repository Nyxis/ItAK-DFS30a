#include "Deck.h"
#include <chrono>
#include <array>
#include <iostream>

namespace rpg {

Deck::Deck(int colors, int values)
    : colors(colors), values(values),
      rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())),
      colorDist(0, colors - 1), valueDist(0, values - 1) {}

std::string toCardString(int colorIndex, int valueIndex) {
    static const std::array<std::string, 4> couleurs = { "♥ Coeur", "♣ Trèfle", "♦ Carreau", "♠ Pique" };
    static const std::array<std::string, 13> valeurs = {
        "As", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "Valet", "Dame", "Roi"
    };

    std::string couleurStr = (colorIndex < static_cast<int>(couleurs.size())) ? couleurs[colorIndex] : "Couleur " + std::to_string(colorIndex + 1);
    std::string valeurStr = (valueIndex < static_cast<int>(valeurs.size())) ? valeurs[valueIndex] : std::to_string(valueIndex + 1);

    return valeurStr + " de " + couleurStr;
}

int Deck::generate() {
    int colorIndex = colorDist(rng);
    int valueIndex = valueDist(rng);
    std::string carte = toCardString(colorIndex, valueIndex);
    std::cout << "Carte tirée : " << carte << std::endl;

    int resultValue = colorIndex * values + valueIndex + 1;
    return resultValue;
}

int Deck::getMax() const {
    return  colors * values;

}

}