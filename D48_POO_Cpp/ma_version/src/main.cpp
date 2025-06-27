#include <iostream>
#include "GameMaster.h"
#include "Encounter.h"
#include "Dice.h"
#include "Coin.h"
#include "Deck.h"

// int main() {
//     rpg::GameMaster gm;

//     std::cout << "Tirages aléatoires par le Game Master :\n" << std::endl;

//     for (int i = 0; i < 5; ++i) {
//         std::cout << "\nTirage #" << i + 1 << " : \n";
//         rpg::Result result = gm.pleaseGiveMeACrit();
//         std::cout << "Résultat: "
//                   << result.getPercent()  << "%"
//                   << " | Statut = " << result.toString()
//                   << std::endl;
//     }

//     return 0;
// }
int main() {
    rpg::GameMaster gm;

    /* Définition des accessoires de jeu, Ne rien ajouter utilisera les accessoires par défaut */
    // gm.addAccessory(std::make_shared<rpg::Dice>(12)); // --> pour ajouter un dé à 12 faces
    // gm.addAccessory(std::make_shared<rpg::Coin>(3));  //  --> pour ajouter une pièce qui sera lancée 3 fois
    // gm.addAccessory(std::make_shared<rpg::Deck>(4, 13)); // --> pour ajouter un jeu de cartes avec 4 couleurs et 13 valeurs

    auto hero1 = std::make_shared<rpg::Adventurer>("Le nain", 1, 50);
    auto hero2 = std::make_shared<rpg::Adventurer>("Le paladin de Dlul", 3, 80);
    gm.registerAdventurer(hero1);
    gm.registerAdventurer(hero2);

    
    rpg::Scenario scenario("La Forêt Interdite");

    auto e1 = std::make_shared<rpg::Encounter>(
        "Combat contre un gobelin",
        "Un petit gobelin surgit des fourrés.",
        5, 30, 75, 100
    );

    auto e2 = std::make_shared<rpg::Encounter>(
        "Trappe piégée",
        "Une dalle s’enfonce sous vos pieds…",
        0, 40, 80, 100
    );

    scenario.addEncounter(e1);
    scenario.addEncounter(e2);

    gm.playScenario(scenario);

    return 0;
}
