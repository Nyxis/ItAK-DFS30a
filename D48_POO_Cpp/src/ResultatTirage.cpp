#include "ResultatTirage.hpp"

ResultatTirage::ResultatTirage(int score, const std::string& type)
    : score(score), type(type) {}

int ResultatTirage::getScore() const {
    return score;
}

std::string ResultatTirage::getType() const {
    return type;
}
