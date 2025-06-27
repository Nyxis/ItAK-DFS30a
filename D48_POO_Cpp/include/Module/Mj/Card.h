#pragma once
#include <string>
#include <iostream>

namespace Jdr::Mj
{
    struct Card
    {
        const std::string color;  // Color of the card
        const std::string value;  // Value of the card
        
        Card(const std::string& color, const std::string& value);
        ~Card() = default;
        
        /**
         * Tests if two cards are equal based on their color and value.
         */
        bool operator==(const Card& other) const;

        /**
         * Renvoie une représentation textuelle de la carte.
         */
        friend std::ostream& operator<<(std::ostream& os, const Card& c);
    };
}
