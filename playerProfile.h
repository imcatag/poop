#ifndef OOP_PLAYERPROFILE_H
#define OOP_PLAYERPROFILE_H


#include <vector>
#include <deque>
#include "autoFarmer.h"
#include "boost.h"

class playerProfile
{
    std::string name;
    long long int balance;

    std::vector<autoFarmer> farmers;
    std::vector<int> count;

    std::deque<boost> boosts;

public:
    [[maybe_unused]] void changeBal(long long int x);
    [[maybe_unused]] void setName(const std::string& s);
    [[maybe_unused]] std::string getName();
    [[maybe_unused]] long long int getBal();
    [[maybe_unused]] std::deque<boost> getBoosts();
    [[maybe_unused]] std::vector<int> getCount();
    [[maybe_unused]] std::vector<autoFarmer> getFarmers();
    playerProfile(const std::string& name_= "untitled");
    playerProfile(const std::string& name_, long long int balance_, const std::vector<autoFarmer>& farmers_, const std::vector<int>& count_,const std::deque<boost>& boosts_);
    playerProfile& operator=(const playerProfile& other);
    [[maybe_unused]] void addBoost (const boost& b);
    [[maybe_unused]] float multi ();
    friend std::ostream& operator<<(std::ostream& os, const playerProfile& p);
    playerProfile(const playerProfile& other);
    ~playerProfile();
};


#endif //OOP_PLAYERPROFILE_H
