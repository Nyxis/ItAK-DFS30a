#include "De.hpp"
#include <cstdlib>
#include <ctime>

De::De(int faces) : nbFaces(faces) {
    std::srand(std::time(nullptr));
}

ResultatTirage De::effectuerTirage() {
    int score = (std::rand() % nbFaces) + 1;
    int pourcentage = static_cast<int>(100.0 * (score - 1) / (nbFaces - 1));
    return ResultatTirage(score, pourcentage);
}
