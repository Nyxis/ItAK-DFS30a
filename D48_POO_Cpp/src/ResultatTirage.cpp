#include "ResultatTirage.hpp"

ResultatTirage::ResultatTirage(int score, int pourcentage)
    : score(score), pourcentage(pourcentage) {}

int ResultatTirage::getScore() const {
    return score;
}

int ResultatTirage::getPourcentage() const {
    return pourcentage;
}
