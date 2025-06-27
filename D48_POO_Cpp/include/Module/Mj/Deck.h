#pragma once
#include "GameAccessory.h"
#include "Card.h"
#include <vector>
#include <string>

namespace Jdr::Mj {
    class Deck : public GameAccessory
    {
        public:
            Deck(
                std::vector<std::string> colors, 
                std::vector<std::string> values
            );
            ~Deck() = default;

            /**
             * Suffles the deck of cards, and select to top card.
             */
            Deck* shuffle();

            /**
             * Reveal the top card of the deck.
             */
            Card revealTopCard() const;

            /**
             * Activates the deck, shuffles it and sets the top card.
             */
            virtual GameAccessory* activate() override;

            /**
             * Overloads the output stream operator to print the deck information.
             */
            friend std::ostream& operator<<(std::ostream& os, const Deck& g);

        private:
            int deckSize;
            std::vector<std::string> colors;
            std::vector<std::string> values;
            std::pair<int, int> topCard;  // Pair of color and value
            
    };
};
