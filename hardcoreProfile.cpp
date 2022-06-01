//
// Created by catag on 5/31/2022.
//

#include "hardcoreProfile.h"

std::shared_ptr<profileMinimal> hardcoreProfile::clone() const {
    return std::make_shared<hardcoreProfile>(*this);
}

hardcoreProfile::hardcoreProfile(const std::string &name_) : profileMinimal(name_)
{
    //std::cout << "Created profile " << name << "\n";
}

hardcoreProfile::hardcoreProfile(const std::string &name_, const long long int bal_) : profileMinimal(name_, bal_)
{

}

void hardcoreProfile::addBoost([[maybe_unused]] const boost &b) {
    std::cout << "\nUnable to buy boosts on hardcore account!\n";
}

void hardcoreProfile::whatIsHardcore() {
    std::cout << "\nThis is a hardcore account. You are not able to buy boosts and farmers.";
}

char hardcoreProfile::profileType() {
    return 'h';
}

void hardcoreProfile::print(std::ostream &os) const {
    const auto& p = *this;
    os << p.name << " " << p.balance << " (HARDCORE)\n";
}
