#pragma once

#include "De.hpp"
#include "Piece.hpp"
#include "Deck.hpp"
#include "Tirage.hpp"
#include "ResultatTirage.hpp"
#include <vector>
#include <string>

struct ResultatGM {
    std::string typeObjet;
    ResultatTirage resultat;
    std::string statut;
};

class GameMaster {
private:
    std::vector<De> des;
    std::vector<Piece> pieces;
    std::vector<Deck> decks;

    std::string evaluerResultat(int pourcentage);

public:
    GameMaster();
    ResultatGM pleaseGiveMeACrit();
};
