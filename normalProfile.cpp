//
// Created by catag on 5/27/2022.
//

#include <iostream>
#include "normalProfile.h"


std::deque<boost> normalProfile::getBoosts() {
    return boosts;
}

std::vector<int> normalProfile::getCount() {
    return count;
}

std::vector<autoFarmer> normalProfile::getFarmers() {
    return farmers;
}


normalProfile::normalProfile(const std::string &name_) : profileMinimal(name_, true) {}

normalProfile::normalProfile(const std::string &name_, long long int balance_, const std::vector<autoFarmer> &farmers_,
                             const std::vector<int> &count_, const std::deque<boost> &boosts_) : profileMinimal(name_,balance_, true), farmers(farmers_), count(count_), boosts(boosts_){}

normalProfile &normalProfile::operator=(const normalProfile &other) {
    name = other.name;
    balance = other.balance;
    farmers = other.farmers;
    count = other.count;
    boosts = other.boosts;
    shopping = other.shopping;
    return *this;
}

void normalProfile::addBoost(const boost &b) {
    boosts.push_back(b);
}

float normalProfile::multi(){
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

char normalProfile::profileType() {
    return 'b';
}

void normalProfile::print(std::ostream &os) const{
    profileMinimal::print(os);
    const auto& p = *this;
    os << "\tfarmers:{";
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
    os << "\n\t}\n";
}

normalProfile::normalProfile(const normalProfile &other) : profileMinimal(other), farmers{other.farmers}, count{other.count}, boosts{other.boosts}{

}

normalProfile::~normalProfile() {

}

std::shared_ptr<profileMinimal> normalProfile::clone() const {
    return std::make_shared<normalProfile>(*this);
}

// deco

normalProfile_decorator::normalProfile_decorator(const normalProfile &profile) : profile(profile) {}

std::ostream &operator<<(std::ostream &os, const normalProfile_decorator &decorator) {
    auto profile = decorator.getProfile();
    os << profile.getName() << "\n";
    os << profile.getBal() << "\n";
    for (const auto& j: profile.getFarmers()) {
        os << j.getName() << " ";
    }
    os << "\n";
    for (auto j: profile.getCount()) {
        os << j << " ";
    }
    os << "\n";
    for (size_t j = 0; j < profile.getBoosts().size(); j++) {
        os << profile.getBoosts()[j].getName() << " " << profile.getBoosts()[j].getUses() << " ";
    }
    os << "\n";
    return os;
}

const normalProfile &normalProfile_decorator::getProfile() const {
    return profile;
}
