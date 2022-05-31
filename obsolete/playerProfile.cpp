//
// Created by yo on 3/22/2022.
//

#include "playerProfile.h"
#include <ostream>

void playerProfile::changeBal(long long int x) {
    balance += x;
}

void playerProfile::setName(const std::string &s) {
    name = s;
}

std::string playerProfile::getName() {
    return name;
}

long long int playerProfile::getBal() {
    return balance;
}

std::deque<boost> playerProfile::getBoosts() {
    return boosts;
}

std::vector<int> playerProfile::getCount() {
    return count;
}

std::vector<autoFarmer> playerProfile::getFarmers() {
    return farmers;
}

playerProfile::playerProfile(const std::string &name_) : name{name_}, balance{0}
{
    //std::cout << "Created profile " << name << "\n";
}

playerProfile::playerProfile(const std::string &name_, long long int balance_, const std::vector<autoFarmer> &farmers_,
                             const std::vector<int> &count_, const std::deque<boost> &boosts_) :
        name{name_}, balance{balance_}, farmers{farmers_}, count{count_}, boosts{boosts_}
{

}

playerProfile &playerProfile::operator=(const playerProfile &other) {
    name = other.name;
    balance = other.balance;
    farmers = other.farmers;
    count = other.count;
    boosts = other.boosts;
    return *this;
}

void playerProfile::addBoost(const boost &b) {
    boosts.push_back(b);
}

float playerProfile::multi() {
    if(boosts.empty()) return 1;
    else
    {
        boosts[0].decBoost();
        if(boosts[0].getUses() <= 0)  boosts.pop_front();
        if(boosts.empty()) return 1;
        else
            return(boosts[0].getMultiplier());
    }
}

std::ostream &operator<<(std::ostream &os, const playerProfile &p) {
    os << "playerProfile: {\n\tname: " << p.name << "\n\tbalance: " << p.balance << "\n\tfarmers:{";
    for(size_t i = 0; i < p.farmers.size(); i++)
    {
        os<< "\n" << "\t" << p.farmers[i].getName() << " x" << p.count[i];
    }
    os << "\n\t}\n\tqueued boosts:{";
    for(int i = 0; i < std::min(3,int(p.boosts.size())); i++)
    {
        os << "\n" << "\t" << p.boosts[i].getName() << " with " << p.boosts[i].getUses() << " uses";
    }
    if(p.boosts.size() > 3) os << "\n\tand " << p.boosts.size() - 3 << " more!";
    os << "\n\t}\n}\n";

    return os;
}

playerProfile::playerProfile(const playerProfile &other) : name{other.name}, balance{other.balance}, farmers{other.farmers}, count{other.count}, boosts{other.boosts}
{

}

playerProfile::~playerProfile() {

}

char playerProfile::profileType() {
    return 'c';
}
