#include "Module/Mj/Deck.h"
#include "Module/Mj/GameAccessory.h"
#include <iostream>    /* std::cout */

namespace Jdr::Mj {

    Deck::Deck(std::vector<std::string> colors, std::vector<std::string> values)
        : colors(std::move(colors)), values(std::move(values))
    {
        this->deckSize = this->colors.size() * this->values.size(); // Total number of cards
    }

    Deck* Deck::shuffle() 
    {
        this->topCard = std::make_pair(
            this->rand(0, this->colors.size() - 1),
            this->rand(0, this->values.size() - 1)
        );

        this->value = this->topCard.first * this->values.size() + this->topCard.second;
        this->score = std::round(
            static_cast<double>((this->topCard.first + 1) * (this->topCard.second + 1)) / 
            this->deckSize * 100.0
        );

        return this;
    }

    GameAccessory* Deck::activate() 
    {
        return this->shuffle();
    }

    Card Deck::revealTopCard() const
    {
        return Card(
            this->colors[this->topCard.first], 
            this->values[this->topCard.second]
        );
    }

    std::ostream& operator<<(std::ostream& os, const Deck& d) {
        os << d.revealTopCard() << "(" << d.score << "%)";
        
        return os;
    }

} // namespace Jdr::Mj
