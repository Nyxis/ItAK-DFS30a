#pragma once

#include "De.hpp"
#include "Piece.hpp"
#include "Deck.hpp"
#include "Tirage.hpp"
#include <vector>
#include <string>

struct ResultatGM {
    std::string typeObjet;
    ResultatTirage resultat;
};

class GameMaster {
private:
    std::vector<De> des;
    std::vector<Piece> pieces;
    std::vector<Deck> decks;

public:
    GameMaster();
    ResultatGM pleaseGiveMeACrit();
};
