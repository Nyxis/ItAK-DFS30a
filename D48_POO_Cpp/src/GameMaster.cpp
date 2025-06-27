#include "GameMaster.hpp"
#include <cstdlib>
#include <ctime>

GameMaster::GameMaster() {
    std::srand(std::time(nullptr));

    des.emplace_back(6);
    des.emplace_back(10);
    des.emplace_back(20);

    pieces.emplace_back(3);
    pieces.emplace_back(3);

    decks.emplace_back(3, 18);
    decks.emplace_back(4, 13);
}

std::string GameMaster::evaluerResultat(int pourcentage) {
    if (pourcentage == 0)
        return "Fumble";
    else if (pourcentage == 100)
        return "Réussite critique";
    else if (pourcentage <= 50)
        return "Échec";
    else
        return "Réussite";
}

ResultatGM GameMaster::pleaseGiveMeACrit() {
    size_t totalObjets = des.size() + pieces.size() + decks.size();
    size_t tirage = static_cast<size_t>(std::rand() % totalObjets);

    ResultatTirage resultat;
    std::string typeObjet;

    if (tirage < des.size()) {
        resultat = des[tirage].effectuerTirage();
        typeObjet = "Dé";
    } else if (tirage < des.size() + pieces.size()) {
        int index = tirage - des.size();
        resultat = pieces[index].effectuerTirage();
        typeObjet = "Pièce";
    } else {
        int index = tirage - des.size() - pieces.size();
        resultat = decks[index].effectuerTirage();
        typeObjet = "Deck";
    }

    std::string statut = evaluerResultat(resultat.getPourcentage());

    return ResultatGM{typeObjet, resultat, statut};
}
