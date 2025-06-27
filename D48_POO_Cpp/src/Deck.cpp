#include "Deck.hpp"
#include "Tirage.hpp"
#include <cstdlib>
#include <ctime>

Deck::Deck(int couleurs, int valeurs)
    : nbCouleurs(couleurs), nbValeurs(valeurs) {
    std::srand(std::time(nullptr));
}

ResultatTirage Deck::effectuerTirage() {
    int couleur = (std::rand() % nbCouleurs) + 1;
    int valeur = (std::rand() % nbValeurs) + 1;

    int score = (couleur - 1) * nbValeurs + valeur;
    int max = nbCouleurs * nbValeurs;

    return Tirage::analyser(score, 1, max);
}
