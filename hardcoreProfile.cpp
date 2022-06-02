//
// Created by catag on 5/31/2022.
//

#include "hardcoreProfile.h"

std::shared_ptr<profileMinimal> hardcoreProfile::clone() const {
    return std::make_shared<hardcoreProfile>(*this);
}

hardcoreProfile::hardcoreProfile(const std::string &name_) : profileMinimal(name_, false) {}

hardcoreProfile::hardcoreProfile(const std::string &name_, long long int bal_) : profileMinimal(name_, bal_, false) {}

void hardcoreProfile::addBoost([[maybe_unused]] const boost &b) {
    std::cout << "\nUnable to buy boosts on hardcore account!\n";
}

char hardcoreProfile::profileType() {
    return 'h';
}

void hardcoreProfile::print(std::ostream &os) const {
    const auto& p = *this;
    os << p.name << " " << p.balance << " (HARDCORE)\n";
}

hardcoreProfile &hardcoreProfile::operator=(const hardcoreProfile &other) {
    balance = other.balance;
    name = other.name;
    shopping = other.shopping;
    return *this;
}

hardcoreProfile::hardcoreProfile(const hardcoreProfile &other) : profileMinimal(other) {}


const hardcoreProfile &hardcoreProfile_decorator::getProfile() const {
    return profile;
}

std::ostream &operator<<(std::ostream &os, const hardcoreProfile_decorator &decorator) {
    auto profilehardcore = decorator.getProfile();
    os << profilehardcore.getName() << "\n" << profilehardcore.getBal() << "\n";
    return os;
}

hardcoreProfile_decorator::hardcoreProfile_decorator(const hardcoreProfile &profile) : profile(profile) {}

