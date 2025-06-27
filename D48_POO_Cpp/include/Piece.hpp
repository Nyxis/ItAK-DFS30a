#ifndef PIECE_HPP
#define PIECE_HPP

#include "ITirable.hpp"
#include "ResultatTirage.hpp"

class Piece : public ITirable {
private:
    int nbLancers;
    int lancerRecursif(int n);

public:
    Piece(int lancers);
    ResultatTirage effectuerTirage() override;
};

#endif
