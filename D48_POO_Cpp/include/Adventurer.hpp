#ifndef ADVENTURER_HPP
#define ADVENTURER_HPP

#include <string>

class Adventurer {
private:
    std::string nom;
    int niveau;
    int pvMax;
    int pvActuels;

public:
    Adventurer(const std::string& nom, int niveau, int pvMax);

    std::string getNom() const;
    int getNiveau() const;
    int getPV() const;
    int getPVMax() const;

    void blesser(int points);
    void soigner(int points);
    void tuer();
    void monterNiveau();
};

#endif
