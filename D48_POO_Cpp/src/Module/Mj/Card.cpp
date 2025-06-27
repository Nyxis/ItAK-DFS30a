#include "Module/Mj/Card.h"
#include <iostream>

namespace Jdr::Mj {

    Card::Card(const std::string& color, const std::string& value)
        : color(color), value(value) {}

    bool Card::operator==(const Card& other) const {
        return this->color == other.color && this->value == other.value;
    }

    std::ostream& operator<<(std::ostream& os, const Card& c) {
        os << c.value << c.color << " ";
        
        return os;
    }

} // namespace Jdr::Mj
