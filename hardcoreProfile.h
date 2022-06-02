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
    explicit hardcoreProfile(const std::string &name_);

    hardcoreProfile(const std::string &name_, long long int bal_);
    void addBoost ([[maybe_unused]] const boost& b) override;

    //[[maybe_unused]] static void whatIsHardcore();

//    [[maybe_unused]] char profileType() override;

    void print(std::ostream& os) const override;

    ~hardcoreProfile() override {};

    hardcoreProfile(const hardcoreProfile& other);

    hardcoreProfile & operator = (const hardcoreProfile &other);

    //

    [[nodiscard]] std::shared_ptr<profileMinimal> clone() const override;

};


class hardcoreProfile_decorator{
public:

    [[maybe_unused]] explicit hardcoreProfile_decorator(const hardcoreProfile &profile);

    friend std::ostream &operator<<(std::ostream &os, const hardcoreProfile_decorator &decorator);

    [[nodiscard]] const hardcoreProfile &getProfile() const;

private:
    hardcoreProfile profile;
};

#endif //OOP_HARDCOREPROFILE_H
