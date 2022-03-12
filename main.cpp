#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <cstdlib>
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

    int getPrice() const
    {
        return price;
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
    int timeInterval;
    int reward;
public:
    autoFarmer(std::string name_ = std::to_string(kaf++), int timeInterval_ = 2048, int reward_ = 0) : name{name_}, timeInterval(timeInterval_), reward(reward_)
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
    explicit playerProfile(std::string name_, long long int balance_, std::vector<autoFarmer> farmers_, std::vector<int> count_, std::deque<boost> boosts_) :
    name{name_}, balance{balance_}, farmers{farmers_}, count{count_}, boosts{boosts_}
    {

    }
    playerProfile& operator=(const playerProfile& other)
    {
        name = other.name;
        balance = other.balance;
        farmers = other.farmers;
        count = other.count;
        boosts = other.boosts;
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
    playerProfile(const playerProfile& other) : name{other.name}, balance{other.balance}, farmers{other.farmers}, count{other.count}, boosts{other.boosts}
    {

    }
    ~playerProfile()
    {

    }
};

void mainMenu()
{
    std::cout << "\np to play\ns for shop\nc to create a copy of current profile\nq to quit\n";
    return;
}

int main()
{
    //initializing a player
    std::vector<playerProfile>  l;
    playerProfile p {"donk"};
    l.push_back(p);
    std::cout << p;
    //init boost list
    std::vector<boost> b;
    boost   b1{"2x1k", 2000, 2, 600},
            b2{"3x1k", 1000, 3, 800},
            b3{"4x500", 500, 4, 1000};
    b.push_back(b1);
    b.push_back(b2);
    b.push_back(b3);
    //init autoFarmer list
    std::vector<autoFarmer> farm;
    autoFarmer  f1{"2@300s", 300, 2},
                f2{"5@600s", 600, 5},
                f3{"12@1200s", 1200, 12};

    //menu hours

    p.changeBal(10000);
    std::cout << p;

    //ACTUAL CODING STARTS
    std::string userInput;
    bool logged = false;
    playerProfile currentProfile;
    while(true)
    {
        if(!logged)
        {
            std::cout << "Choose a profile\n";
            std::ifstream f("players.txt");

            std::string playerName;
            long long int bal;
            char line[10001];

            std::vector<autoFarmer> farmers;
            std::vector<int> count;

            std::deque<boost> boosts;
            std::string boostname;
            int boostuses;
            while(f>>playerName) // read all playerdata file
            {
                farmers.clear();
                count.clear();
                boosts.clear();
                f >> bal;
                f.get();
                f.getline(line,sizeof(line));
                char * pch;

                pch = std::strtok(line, " "); // farmers
                while(pch != NULL)
                {
                    for(auto i : farm)
                    {
                        bool matching = true;
                        for(size_t j = 0; j < i.getName().size() ; j ++)
                            if (i.getName()[j] != pch[j]) {matching = false; break;}
                        if(matching)
                        {
                            farmers.push_back(i);
                        }
                    }
                    pch = std::strtok(NULL, " ");
                }

                pch = std::strtok(line, " "); // count
                while(pch != NULL)
                {
                    count.push_back(atoi(pch));
                    pch = std::strtok(NULL, " ");
                }

                pch = std::strtok(line, " "); // boosts
                while(pch != NULL)
                {
                    boostname = pch;
                    pch = std::strtok(NULL, " ");
                    boostuses = atoi(pch);

                    for(auto i : b)
                    {
                        bool matching = true;
                        for(size_t j = 0; j < i.getName().size() ; j ++)
                            if (i.getName()[j] != pch[j]) {matching = false; break;}
                        if(matching)
                        {
                            boost aub{boostname, boostuses, i.getMultiplier(), i.getPrice()};
                            boosts.push_back(aub);
                        }
                    }

                    pch = std::strtok(NULL, " ");
                }
                playerProfile aup {playerName, bal, farmers, count, boosts};
                l.push_back(aup);
                std::cout << aup << "\n";
            }
            f.close();
            while(true)
            {
                 std::cin >> userInput;
                 bool matching = false;
                 for(auto i : l)
                 {
                     if(userInput == i.getName())
                     {
                         matching = true;
                         currentProfile = i;
                         std::cout << "profile selected: " << userInput << "\n";
                         break;
                     }
                 }
                 if(matching) break;
                 else
                     std::cout << "profile not found\n";
            }

        }
        while(true)
        {
            std::cout << "Yo. Choose an option.\n";
            mainMenu();
            std::cin >> userInput;

            break;
        }

        break;
    }

    return 0;
}
