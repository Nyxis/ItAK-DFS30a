#ifndef DECK_HPP
#define DECK_HPP

#include "ITirable.hpp"

class Deck : public ITirable {
private:
    int nbCouleurs;
    int nbValeurs;

public:
    Deck(int couleurs, int valeurs);
    ResultatTirage effectuerTirage() override;
};

#endif
