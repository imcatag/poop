//
// Created by catag on 5/31/2022.
//

#ifndef OOP_HARDCOREPROFILE_H
#define OOP_HARDCOREPROFILE_H


#include <iostream>
#include "profileMinimal.h"

class [[maybe_unused]] hardcoreProfile : public profileMinimal
{
public:
    [[maybe_unused]] explicit hardcoreProfile(const std::string &name_) : profileMinimal(name_)
    {
        //std::cout << "Created profile " << name << "\n";
    };

    [[maybe_unused]] hardcoreProfile(const std::string &name_, const long long int bal_) : profileMinimal(name_, bal_)
    {

    };
    void addBoost ([[maybe_unused]] const boost& b) override
    {
        std::cout << "\nUnable to buy boosts on hardcore account!\n";
    }

    [[maybe_unused]] static void whatIsHardcore()
    {
        std::cout << "\nThis is a hardcore account. You are not able to buy boosts and farmers.";
    }

    [[maybe_unused]] char profileType() override
    {
        return 'h';
    };

    ~hardcoreProfile() override {};

};


#endif //OOP_HARDCOREPROFILE_H
