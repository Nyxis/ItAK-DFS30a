#include "Module/Mj/Coin.h"
#include "Module/Mj/GameAccessory.h"
#include <iostream>      
#include <cmath>        /* round / ceil / floor */
#include <vector>       /* = arrays */

namespace Jdr::Mj {

    /**
     * Le pourcentage de chances de faire pile x fois de suite : proba = (1/2)^(nbLancés + 1)
     * On utilise cette formule pour calculer les scores, en applatissant les extrémités à 0 et 100 avec un coef d'amortissement
     */
    Coin::Coin(int nbFlips) : nbFlips(nbFlips) 
    {
        double tappering = 20;
        double max = 1.0 - std::pow(
            0.5,          // une chance sur 2
            nbFlips
        );
        
        int nbOutcomes = nbFlips + 1;               // il faut ajouter le "full loose"
        this->scoreLadder.resize(nbOutcomes);       // allocation mémoire du tableau

        this->scoreLadder[0] = 0;                   // full loose
        this->scoreLadder[nbOutcomes-1] = 100;      // full win

        for (int i = 1; i < nbFlips; i++) {         // mixed cases
            double proba = 1.0 - std::pow(0.5, i);
            this->scoreLadder[i] = std::round(
                proba / max * 100.0 -                                               // raw probability
                tappering * (1.0 - static_cast<double>(i - 1) / (nbFlips - 1))      // exponential tappering
            );
        }
    }

    int Coin::flipUntilFailureOrMaxFlips(int currentFlip)
    {
        // this est un pointeur sur l'objet courant, accéder à un membre se fait avec la flèche ->
        if (currentFlip >= this->nbFlips) {
            return currentFlip;
        }

        return this->randomizer.rand(1) ? // 0 for tails, 1 for heads
            this->flipUntilFailureOrMaxFlips(currentFlip + 1) :
            currentFlip - 1;
    }

    Coin* Coin::flip()
    {
        this->value = this->flipUntilFailureOrMaxFlips(1 /* start from the first flip */);
        this->score = this->scoreLadder[this->value];

        return this;
    }
    
    GameAccessory* Coin::activate()
    {
        return this->flip();
    }
};
