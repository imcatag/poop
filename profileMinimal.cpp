//
// Created by catag on 5/18/2022.
//

#include <ostream>
#include <iostream>
#include "profileMinimal.h"

void profileMinimal::changeBal(long long int x) {
    balance += x;
}

void profileMinimal::setName(const std::string &s) {
    name = s;
}

std::string profileMinimal::getName() {
    return name;
}

long long int profileMinimal::getBal() {
    return balance;
}

profileMinimal::profileMinimal(const std::string &name_, bool shopping_) : name{name_}, balance{0}, shopping(shopping_)
{
    //std::cout << "Created profile " << name << "\n";
}


profileMinimal &profileMinimal::operator=(const profileMinimal &other) {
    name = other.name;
    balance = other.balance;
    shopping = other.shopping;
    return *this;
}


[[maybe_unused]] float profileMinimal::multi() {
    return 1;
}

[[maybe_unused]] profileMinimal::profileMinimal(const profileMinimal &other) : name{other.name}, balance{other.balance}, shopping(other.shopping)
{

}

profileMinimal::~profileMinimal() {

}

void profileMinimal::addBoost([[maybe_unused]] const boost &b) {
    std::cout << "this is an undefined profile type";

}

profileMinimal::profileMinimal(const std::string &name, long long int balance, bool shopping_) : name(name), balance(balance), shopping(shopping_) {}

std::ostream &operator<<(std::ostream &os, const profileMinimal& profile) {
    profile.print(os);
    return os;
}

void profileMinimal::print(std::ostream &os) const {
    const auto& p = *this;
    os << p.name << " " << p.balance << "\n";
}

bool profileMinimal::canUseShop() const {
    return shopping;
}
