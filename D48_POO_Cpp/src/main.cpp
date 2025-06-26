#include <iostream>
#include "GameMaster.h"

int main() {
    rpg::GameMaster gm;

    std::cout << "Tirages aléatoires par le Game Master :\n" << std::endl;

    for (int i = 0; i < 5; ++i) {
        std::cout << "\nTirage #" << i + 1 << " : \n";
        rpg::Result result = gm.pleaseGiveMeACrit();
        std::cout << "Résultat: "
                  << result.getPercent()  << "%"
                  << " | Statut = " << result.toString()
                  << std::endl;
    }

    return 0;
}
