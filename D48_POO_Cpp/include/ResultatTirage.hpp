#ifndef RESULTATTIRAGE_HPP
#define RESULTATTIRAGE_HPP

#include <string>

class ResultatTirage {
public:
    ResultatTirage(int score, const std::string& type);
    ResultatTirage() : score(0), type("Inconnu") {}

    int getScore() const;
    std::string getType() const;

private:
    int score;
    std::string type;
};

#endif
