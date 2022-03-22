#include "autoFarmer.h"

autoFarmer::autoFarmer(const std::string &name_, int timeInterval_, int reward_) : name{name_}, timeInterval(timeInterval_), reward(reward_)
{
    //std::cout << "\nconstr init autoFarmer " << name << "\n";
}

std::ostream &operator<<(std::ostream &os, const autoFarmer &p) {
    os << "autoFarmer: {\n\tname: " << p.name << "\n\tbalance: " << p.timeInterval << "\n\treward: " << p.reward;
    return os;
}

autoFarmer::~autoFarmer() {

}
