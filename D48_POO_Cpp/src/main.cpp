#include <iostream>
#include <vector>
#include "Module/Mj/Coin.h"
#include "Module/Mj/Dice.h"
#include "Module/Mj/Deck.h"
#include "Module/Mj/GameMaster.h"
#include "Module/Encounter/Result.h"
#include "Module/Encounter/Outcome.h"

/**
 * @param int argc       number of command line arguments
 * @param char* argv[]   array of command line arguments
 */
int main()
{
    using namespace Jdr::Mj;
    using namespace Jdr::Encounter;
    
    Coin coin4(4); // 🦆
    std::cout << "Coin with 4 flips :" << std::endl;
    for (int i = 0; i<20; i++) {

        coin4.flip();
        std::cout << "🪙" << coin4 << " - ";
    }
    std::cout << std::endl << std::endl;

    Coin coin10(10); // 🦆
    std::cout << "Coin with 10 flips :" << std::endl;
    for (int i = 0; i<20; i++) {
        coin10.flip();
        std::cout << "🪙" << coin10 << " - ";
    }
    std::cout << std::endl << std::endl;
    
    Dice dice6(6);
    std::cout << "Dice with 6 sides :" << std::endl;
    for (int i = 0; i<20; i++) {
        dice6.roll();
        std::cout << "🎲" << dice6 << " - ";
    }
    std::cout << std::endl << std::endl;

    Dice dice20(20);
    std::cout << "Dice with 20 sides :" << std::endl;
    for (int i = 0; i<20; i++) {
        dice20.roll();
        std::cout << "🎲" << dice20 << " - ";
    }
    std::cout << std::endl << std::endl;

    Deck classicDeck(
        {"♦️", "♠️", "♥️", "♣️"},
        {"2", "3", "4", "5", "6", "7", "8", "9", "10", "V", "Q", "K", "1"}
    );
    std::cout << "Classic deck (54 cards) :" << std::endl;
    for (int i = 0; i<20; i++) {
        classicDeck.shuffle();
        std::cout << classicDeck << " - ";
    }
    std::cout << std::endl << std::endl;

    Deck fantasyDeck(
        {"⚽", "🎳", "🥌"},
        {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"}
    );
    std::cout << "Fantasy deck (60 cards) :" << std::endl;
    for (int i = 0; i<20; i++) {
        fantasyDeck.shuffle();
        std::cout << fantasyDeck << " - ";
    }
    std::cout << std::endl << std::endl;

    GameMaster gameMaster({
        &coin4, &coin10, &dice6, &dice20, &classicDeck, &fantasyDeck
    });

    for (int i = 0; i < 30; i++) {
        Result result = gameMaster.pleaseGiveMeACrit();
        std::cout << result << std::endl;
    }

    return 0;
}
