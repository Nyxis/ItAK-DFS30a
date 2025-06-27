#include "Tirage.hpp"

ResultatTirage Tirage::analyser(int score, int min, int max) {
    int mediane = (min + max) / 2;
    std::string type;

    if (score == min)
        type = "Fumble";
    else if (score == max)
        type = "Réussite critique";
    else if (score <= mediane)
        type = "Échec";
    else
        type = "Réussite";

    return ResultatTirage(score, type);
}
