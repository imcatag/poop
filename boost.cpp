#include "boost.h"

boost::boost(const std::string &name_, int uses_, float multiplier_, int price_) :
        name{name_}, uses{uses_}, price{price_}, multiplier{multiplier_}
{
    //std::cout << "Init boost " << name << "\n";
}

void boost::decBoost() {
    uses--;
}

std::string boost::getName() const {
    return name;
}

float boost::getMultiplier() const {
    return multiplier;
}

int boost::getUses() const {
    return uses;
}

int boost::getPrice() const {
    return price;
}

std::ostream &operator<<(std::ostream &os, const boost &p) {
    os << "boost: {\n\tname: " << p.name << "\n\tuses: " << p.uses << "\n\tmultiplier: " << p.multiplier << "\n\tprice: " << p.price << "}";
    return os;
}

boost::~boost() {

}
