#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
int kaf = 0, kb = 0;
class boost
{
    std::string name;
    int uses;
    int price;
    float multiplier;
public:
    explicit boost (std::string name_ = std::to_string(kb++), int uses_ = 1000, float multiplier_ = 2, int price_ = 300) :
    name{name_}, uses{uses_}, price{price_}, multiplier{multiplier_}
    {
        std::cout << "Init boost " << name << "\n";
    }

    [[maybe_unused]] void fuckWerrorslmaoicantevenhaveintpriceinmycodesinceitsnotusedyetanditgeneratesawarning()
    {
        price++;
    }
    void decBoost()
    {
        uses--;
    }
    std::string getName() const
    {
        return name;
    }
    float getMultiplier() const
    {
        return multiplier;
    }

    int getUses() const
    {
        return uses;
    }
    friend std::ostream& operator<<(std::ostream& os, const boost& p)
    {
        os << "autoFarmer: {\n\tname: " << p.name << "\n\tuses: " << p.uses << "\n\tmultiplier: " << p.multiplier << "}";
        return os;
    }
};
class autoFarmer
{
    std::string name;
    float timeInterval;
    int reward;
public:
    autoFarmer(std::string name_ = std::to_string(kaf++), float timeInterval_ = 2048, int reward_ = 0) : name{name_}, timeInterval(timeInterval_), reward(reward_)
    {
        std::cout << "\nconstr init autoFarmer " << name << "\n";
    }
    std::string getName() const
    {
        return name;
    }
    [[maybe_unused]] float getTime() const
    {
        return timeInterval;
    }

    [[maybe_unused]] int getReward() const
    {
        return reward;
    }
    friend std::ostream& operator<<(std::ostream& os, const autoFarmer& p)
    {
        os << "autoFarmer: {\n\tname: " << p.name << "\n\tbalance: " << p.timeInterval << "\n\treward: " << p.reward;
        return os;
    }

    ~autoFarmer()
    {

    }

};

class playerProfile
{
    std::string name;
    long long int balance;

    std::vector<autoFarmer> farmers;
    std::vector<int> count;

    std::deque<boost> boosts;

public:
    void changeBal(long long int x)
    {
        balance += x;
    }
    [[maybe_unused]] std::string getName()
    {
        return name;
    }
    [[maybe_unused]] long long int getBal()
    {
        return balance;
    }
    [[maybe_unused]] std::deque<boost> getBoosts()
    {
        return boosts;
    }
    [[maybe_unused]] std::vector<int> getCount()
    {
        return count;
    }
    [[maybe_unused]] std::vector<autoFarmer> getFarmers()
    {
        return farmers;
    }
    explicit playerProfile(std::string name_= "untitled") : name{name_}, balance{0}
    {
        std::cout << "Created profile " << name << "\n";
    }
    playerProfile& operator=(const playerProfile& other)
    {
        name = other.name;
        balance = other.balance;
        farmers = other.farmers;
        count = other.count;
        return *this;
    }
    [[maybe_unused]] void addBoost (const boost b)
    {
        boosts.push_back(b);
    }
    [[maybe_unused]] float multi ()
    {
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
    friend std::ostream& operator<<(std::ostream& os, const playerProfile& p)
    {
        os << "playerProfile: {\n\tname: " << p.name << "\n\tbalance: " << p.balance << "\n\tfarmers:\n{";
        for(size_t i = 0; i < p.farmers.size(); i++)
        {
            os<< "\n" << "\t" << p.farmers[i].getName() << " x" << p.count[i];
        }
        os << "}\n\tqueued boosts:\n{";
        for(size_t i = 0; i < p.boosts.size(); i++)
        {
            os << "\n" << "\t" << p.boosts[i].getName();
        }
        os << "}\n}\n";

        return os;
    }
    ~playerProfile()
    {

    }
};

int main()
{
    //initializing a player
    std::vector<playerProfile>  l;
    playerProfile p {"donk"};
    l.push_back(p);
    std::cout << p;
    //initialising booster list
    std::vector<boost> b;
    boost b1{"2x1k", 2000, 2, 600}, b2{"3x1k", 1000, 3, 800}, b3{"4x500", 500, 4, 1000};
    b.push_back(b1);
    b.push_back(b2);
    b.push_back(b3);
    //autofarmers mai dureaza :) - sunt usor de setat

    //menu hours

    p.changeBal(10000);
    std::cout << p;

    //ACTUAL CODING STARTS
    while(true)
    {
        cout << "Yo. Choose an option.\n";

        break;
    }
    return 0;
}
