#include "De.hpp"
#include "Tirage.hpp"
#include <cstdlib>
#include <ctime>

De::De(int faces) : nbFaces(faces) {
    std::srand(std::time(nullptr));
}

ResultatTirage De::effectuerTirage() {
    int score = (std::rand() % nbFaces) + 1;
    return Tirage::analyser(score, 1, nbFaces);
}
