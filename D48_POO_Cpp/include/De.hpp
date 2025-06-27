#ifndef DE_HPP
#define DE_HPP

#include "ITirable.hpp"

class De : public ITirable {
private:
    int nbFaces;

public:
    De(int faces);
    ResultatTirage effectuerTirage() override;
};

#endif
