#ifndef TIRAGE_HPP
#define TIRAGE_HPP

#include "ResultatTirage.hpp"

class Tirage {
public:
    static ResultatTirage analyser(int score, int min, int max);
};

#endif

