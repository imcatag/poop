//
// Created by catag on 5/27/2022.
//

#ifndef OOP_NORMALPROFILE_H
#define OOP_NORMALPROFILE_H


#include <vector>
#include <deque>
#include <ostream>
#include "profileMinimal.h"
#include "autoFarmer.h"

class normalProfile : public profileMinimal {
private:
    std::vector<autoFarmer> farmers;
    std::vector<int> count;
    std::deque<boost> boosts;

public:
    std::deque<boost> getBoosts();
    std::vector<int> getCount();
    std::vector<autoFarmer> getFarmers();
    explicit normalProfile(const std::string& name_= "untitled");
    normalProfile(const std::string& name_, long long int balance_, const std::vector<autoFarmer>& farmers_, const std::vector<int>& count_,const std::deque<boost>& boosts_);
    normalProfile& operator=(const normalProfile& other);
    normalProfile(const normalProfile& other);
    void addBoost(const boost& b) override;
    float multi() override;
    [[maybe_unused]] char profileType() override;
    void print(std::ostream &os) const override;
    ~normalProfile() override;



    //

    [[nodiscard]] std::shared_ptr<profileMinimal> clone() const override;
};

class normalProfile_decorator{
public:
    [[maybe_unused]] explicit normalProfile_decorator(const normalProfile &profile);

    friend std::ostream &operator<<(std::ostream &os, const normalProfile_decorator &decorator);

    [[nodiscard]] const normalProfile &getProfile() const;

private:
    normalProfile profile;
};
#endif //OOP_NORMALPROFILE_H
