#define _CRT_SECURE_NO_WARNINGS
//fix strtok in MSVC
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "effolkronium/random.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define toclear "cls"
#define cp "copy"
#else
#define toclear "clear"
#define cp "cp"
#endif

using Random = effolkronium::random_static;

int kaf = 0, kb = 0;
class boost
{
    std::string name;
    int uses;
    int price;
    float multiplier;
public:
    explicit boost (const std::string& name_ = std::to_string(kb++), int uses_ = 1000, float multiplier_ = 2, int price_ = 300) :
            name{name_}, uses{uses_}, price{price_}, multiplier{multiplier_}
    {
        //std::cout << "Init boost " << name << "\n";
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
        os << "boost: {\n\tname: " << p.name << "\n\tuses: " << p.uses << "\n\tmultiplier: " << p.multiplier << "\n\tprice: " << p.price << "}";
        return os;
    }
};
class autoFarmer
{
    std::string name;
    int timeInterval;
    int reward;
public:
    autoFarmer(const std::string& name_ = std::to_string(kaf++), int timeInterval_ = 2048, int reward_ = 0) : name{name_}, timeInterval(timeInterval_), reward(reward_)
    {
        //std::cout << "\nconstr init autoFarmer " << name << "\n";
    }
    std::string getName() const
    {
        return name;
    }
    /*[[maybe_unused]] int getTime() const
    {
        return timeInterval;
    }*/

    /*[[maybe_unused]] int getReward() const
    {
        return reward;
    }*/
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
    [[maybe_unused]] void changeBal(long long int x)
    {
        balance += x;
    }
    [[maybe_unused]] void setName(const std::string& s)
    {
        name = s;
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
    playerProfile(const std::string& name_= "untitled") : name{name_}, balance{0}
    {
        //std::cout << "Created profile " << name << "\n";
    }
    playerProfile(const std::string& name_, long long int balance_, const std::vector<autoFarmer>& farmers_, const std::vector<int>& count_,const std::deque<boost>& boosts_) :
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
    [[maybe_unused]] void addBoost (const boost& b)
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
        os << "playerProfile: {\n\tname: " << p.name << "\n\tbalance: " << p.balance << "\n\tfarmers:{";
        for(size_t i = 0; i < p.farmers.size(); i++)
        {
            os<< "\n" << "\t" << p.farmers[i].getName() << " x" << p.count[i];
        }
        os << "\n\t}\n\tqueued boosts:{";
        for(int i = 0; i < std::min(3,int(p.boosts.size())); i++)
        {
            os << "\n" << "\t" << p.boosts[i].getName() << " with " << p.boosts[i].getUses() << " uses";
        }
        if(p.boosts.size() > 3) os << "\n\tand " << p.boosts.size() - 3 << " more!";
        os << "\n\t}\n}\n";

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
    std::cout << "\np to play\ns for shop\nc to create a copy of current profile\nq to save and quit\n";
    return;
}
std::vector<std::string> wl;
std::vector<boost> b;
std::vector<playerProfile>  l;
std::vector<autoFarmer> farm;
playerProfile currentProfile;
std::string userInput;
bool logged = false;
int letterVal[] = {1, 3, 3, 2, 1, 4,
                   2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10,
                   1, 1, 1, 1, 4, 4, 8, 4, 10}; // from scrabble, idk if accurate

void initboostfarmer()
{
    boost   b1{"2x1k", 2000, 2, 600},
            b2{"3x1k", 1000, 3, 800},
            b3{"4x500", 500, 4, 1000};
    b.push_back(b1);
    b.push_back(b2);
    b.push_back(b3);

    autoFarmer  f1{"2@300s", 300, 2},
            f2{"5@600s", 600, 5},
            f3{"12@1200s", 1200, 12};
    farm.push_back(f1);
    farm.push_back(f2);
    farm.push_back(f3);
}

void wordlistvector()
{
    std::string word;
    std::ifstream f("smallwordlist.txt");
    for(int i = 1; i <= 16750; i++)
    {
        f >> word;
        for(int j=1; j<= log(16751 - i )/log(10) + 1; j++)
        {
            wl.push_back(word);
        }
    }
    //std::cout << wl.size();
    return;
}
int main()
{
    initboostfarmer();
    wordlistvector();

    int failcount = 0;

    while(true)
    {
        if(!logged) // login, but there is no logout feature yet
        {
            std::cout << "Choose a profile or type \'new\' to create a new profile\n";
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
                            if (i.getName()[j] != pch[j])
                            {
                                matching = false;
                                break;
                            }
                        if(matching)
                        {
                            farmers.push_back(i);
                        }
                    }
                    pch = std::strtok(NULL, " ");
                }
                f.getline(line,sizeof(line));
                pch = std::strtok(line, " "); // count
                while(pch != NULL)
                {
                    count.push_back(atoi(pch));
                    pch = std::strtok(NULL, " ");
                }
                f.getline(line,sizeof(line));
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
                            if (i.getName()[j] != boostname[j])
                            {
                                matching = false;
                                break;
                            }
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
            while(true) // profile selection loop
            {
                if(logged) break;
                std::cin >> userInput;
                if(userInput == "q" || userInput == "Q") return 0;
                else if(userInput == "new")
                    while(true)
                    {
                        std::cout << "Name your profile: ";
                        std::cin >> userInput;
                        bool nameused = false;
                        for (auto i: l)
                        {
                            if (i.getName() == userInput)
                            {
                                nameused = true;
                                break;
                            }
                        }
                        if (!nameused)
                        {
                            playerProfile aup{userInput};
                            currentProfile = aup;
                            l.push_back(currentProfile);
                            logged = true;
                            break;
                        }
                    }
                else
                {

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
                    if(matching)
                    {
                        logged = true;
                        break;
                    }
                    else
                    {
                        std::cout << "profile not found\n";
                        failcount ++;
                    }
                    if(failcount >= 5) break;
                }
            }

        }
        while(true)
        {
            system(toclear);
            std::cout << "Yo. Choose an option. Playing on profile "<< currentProfile.getName() << "\n";
            mainMenu();
            std::cin >> userInput;
            if(userInput[0] == 'q' || userInput[0] == 'Q')
            {
                char cop[1001] = cp;
                strcat(cop, " players.txt players_obsolete.txt");
                system(cop);
                for(size_t i = 0; i < l.size(); i ++)
                {
                    if(l[i].getName() == currentProfile.getName())
                        l.erase(l.begin() + i);
                }
                l.push_back(currentProfile);
                std::ofstream g("players.txt");
                for (auto i : l)
                {
                    g << i.getName() << "\n";
                    g << i.getBal() << "\n";
                    for(auto j : i.getFarmers())
                    {
                        g << j.getName() << " ";
                    }
                    g << "\n";
                    for(auto j : i.getCount())
                    {
                        g << j << " ";
                    }
                    g << "\n";
                    for(size_t j = 0; j < i.getBoosts().size(); j ++)
                    {
                        g << i.getBoosts()[j].getName() << " " << i.getBoosts()[j].getUses() << " ";
                    }
                    g << "\n";

                }
                return 0;
            }
            else if(userInput[0] == 'c' || userInput[0] == 'C')
            {
                playerProfile aup = currentProfile;
                aup.setName("copy of " + currentProfile.getName());
                l.push_back(aup);
            }
            else if(userInput[0] == 'p' || userInput[0] == 'P') // play cycle
            {
                //std::cout << "This is totally implemented.\n";
                std::cout << "q to quit\n";
                //sleep but better lmao
                for (int i = 1; i <= 100000000; i ++)
                {
                    i++;
                    i--;
                }
                std::cout << "GET READY TO TYPE.\n";
                for (int i = 1; i <= 100000000; i ++)
                {
                    i++;
                    i--;
                }
                std::cout << "3.\n";
                for (int i = 1; i <= 100000000; i ++)
                {
                    i++;
                    i--;
                }
                std::cout << "2.\n";
                for (int i = 1; i <= 100000000; i ++)
                {
                    i++;
                    i--;
                }
                std::cout << "1.\n";
                for (int i = 1; i <= 40000000; i ++)
                {
                    i++;
                    i--;
                }
                std::cout << "GO!\n";
                for (int i = 1; i <= 40000000; i ++)
                {
                    i++;
                    i--;
                }
                getline(std::cin, userInput);
                while(true)
                {
                    system(toclear);
                    std::string s = "";
                    int nr = 0;
                    int totalvalue = 0;
                    int numberowords = Random::get(10,12);
                    int nonmatch = 0;
                    int w = 0;
                    for(int i = 1; i <= numberowords; i ++)
                    {
                        int wordrand = Random::get(0,int(wl.size()-1));
                        if(i != 1) s+= " ";
                        s += wl[wordrand];
                    }
                    std::cout << s << "\n";
                    getline(std::cin, userInput);
                    if(userInput == "q" || userInput == "Q" || userInput.empty())
                        break;
                    for (unsigned long long int i = 0; i < std::min(s.size(), userInput.size()); i++)
                    {
                        if (s[i] != userInput[i])
                            nonmatch++;
                    }
                    for(char i : s)
                    {
                        if(i!=' ')
                        {
                            nr ++;
                            totalvalue += letterVal[i - 'a'];
                        }
                    }
                    w = int(std::max(0, numberowords * totalvalue * (100 - nonmatch*nonmatch) / 100 / nr) * currentProfile.multi());
                    currentProfile.changeBal(w);
                    std::cout << w;
                    for (int i = 1; i <= 200000000; i ++)
                    {
                        i++;
                        i--;
                    }
                }
            }
            else if(userInput[0] == 's' || userInput[0] == 'S')
            {
                system(toclear);
                std::cout << "b for boosts\nf for autofarmers\n";
                std::cin >> userInput;
                if(userInput[0] == 'b' || userInput[0] == 'B')
                {
                    system(toclear);
                    for(auto i : b)
                    {
                        std::cout << i << "\n";
                    }
                    std::cout << "name the boost you want to buy or quit with 'q'\n";
                    std::cin >> userInput;
                    if(userInput[0] == 'q' || userInput[0] == 'Q')
                        continue;
                    else
                    {
                        bool found = false;
                        for(auto i : b)
                        {
                            if(i.getName() == userInput)
                            {
                                if(currentProfile.getBal() > i.getPrice())
                                {
                                    currentProfile.changeBal(-i.getPrice());
                                    currentProfile.addBoost(i);
                                }
                                else
                                {
                                    std::cout << "NO MONEY!\n";
                                    system("pause");
                                }
                                found = true;
                            }
                        }
                        if(!found)
                        {
                            std::cout << "Can't find that boost!\n";
                            system("pause");
                        }
                    }
                }

                else if(userInput[0] == 'f' || userInput[0] == 'F')
                {
                    system(toclear);
                    for(auto i : farm)
                    {
                        std::cout << i << "\n";
                    }
                    std::cout << "This is totally implemented.\n";
                    system("pause");
                }
            }
            else return 0;
        }

        break;
    }

    return 0;
}
