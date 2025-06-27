#ifndef ITIRABLE_HPP
#define ITIRABLE_HPP

#include "ResultatTirage.hpp"

class ITirable {
public:
    virtual ResultatTirage effectuerTirage() = 0;
    virtual ~ITirable() = default;
};

#endif
