#ifndef RESULTATTIRAGE_HPP
#define RESULTATTIRAGE_HPP

class ResultatTirage {
public:
    ResultatTirage(int score, int pourcentage);
    ResultatTirage() : score(0), pourcentage(0) {}

    int getScore() const;
    int getPourcentage() const;

private:
    int score;
    int pourcentage;
};

#endif
