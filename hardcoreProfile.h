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
    [[maybe_unused]] explicit hardcoreProfile(const std::string &name_);

    [[maybe_unused]] hardcoreProfile(const std::string &name_, const long long int bal_);
    void addBoost ([[maybe_unused]] const boost& b) override;

    [[maybe_unused]] static void whatIsHardcore();

    [[maybe_unused]] char profileType() override;

    void print(std::ostream& os) const override;

    ~hardcoreProfile() override {};

    //

    std::shared_ptr<profileMinimal> clone() const override;

};


#endif //OOP_HARDCOREPROFILE_H
