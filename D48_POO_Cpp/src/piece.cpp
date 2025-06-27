#include "Piece.hpp"
#include <cstdlib>
#include <ctime>

Piece::Piece(int lancers) : nbLancers(lancers) {
    std::srand(std::time(nullptr));
}

int Piece::lancerRecursif(int n) {
    if (n == 0) return 0;
    int tirage = std::rand() % 2;
    return tirage + lancerRecursif(n - 1);
}

ResultatTirage Piece::effectuerTirage() {
    int totalFace = lancerRecursif(nbLancers);
    int pourcentage = static_cast<int>(100.0 * totalFace / nbLancers);
    return ResultatTirage(totalFace, pourcentage);
}
