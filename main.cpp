//#define _CRT_SECURE_NO_WARNINGS
//fix strtok in MSVC
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <cmath>
#include <filesystem>
#include "ext/random.hpp"
#include "boost.h"
#include "autoFarmer.h"
#include "playerProfile.h"
#include "wordlist.h"
#include "ext/rlutil/rlutil.h"
#define arrsize 5584
using Random = effolkronium::random_static;
namespace fs = std::filesystem;


void mainMenu()
{
    std::cout << "\np to play\ns for shop\nc to create a copy of current profile\nq to save and quit\n";
}


std::vector<boost> initboost() {
    std::vector<boost> b;
    boost b1{"2x1k", 2000, 2, 600},
            b2{"3x1k", 1000, 3, 800},
            b3{"4x500", 500, 4, 1000};
    b.push_back(b1);
    b.push_back(b2);
    b.push_back(b3);
    return b;
}
std::vector<autoFarmer> initfarmer(){
    std::vector<autoFarmer> f;
    autoFarmer  f1{"2@300s", 300, 2},
            f2{"5@600s", 600, 5},
            f3{"12@1200s", 1200, 12};
    f.push_back(f1);
    f.push_back(f2);
    f.push_back(f3);
    return f;
}

int main()
{
    std::vector<boost> b = initboost();
    std::vector<playerProfile>  l;
    std::vector<autoFarmer> farm = initfarmer();
    playerProfile currentProfile;
    std::string userInput;
    bool logged = false;
    const int letterVal[] = {1, 3, 3, 2, 1, 4,
                       2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10,
                       1, 1, 1, 1, 4, 4, 8, 4, 10}; // from scrabble, idk if accurate
    int failcount = 0;
    fs::create_directories("userdata");
    while(true)
    {
        if(!logged) // login, but there is no logout feature yet
        {
            std::cout << "Choose a profile or type \'new\' to create a new profile\n";
            std::ifstream testforfile("userdata/players.txt");
            if(!testforfile.good())
            {
                std::cout << "no file\n";
                testforfile.close();
                std::ofstream g("userdata/players.txt");
                g << "";
                g.close();
            }
            testforfile.close();
            std::ifstream f("userdata/players.txt");

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


                pch = std::strpbrk(line, " "); // farmers
                while(pch != nullptr)
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
                    pch = std::strpbrk(pch+1, " ");
                }
                f.getline(line,sizeof(line));
                pch = std::strpbrk(line, " "); // count
                while(pch != nullptr)
                {
                    count.push_back(atoi(pch));
                    pch = std::strpbrk(pch + 1, " ");
                }
                f.getline(line,sizeof(line));
                pch = std::strpbrk(line, " "); // boosts
                while(pch != nullptr)
                {
                    boostname = pch;
                    pch = std::strpbrk(pch+1, " ");
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

                    pch = std::strpbrk(pch + 1, " ");
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
            rlutil::cls();
            std::cout << "Yo. Choose an option. Playing on profile "<< currentProfile.getName() << "\n";
            mainMenu();
            std::cin >> userInput;
            if(userInput[0] == 'q' || userInput[0] == 'Q')
            {
//                char cop[1001] = cp;
//                strcat(cop, " players.txt players_obsolete.txt");1
//                system(cop);
//                std::cout << cop;
                std::ifstream f("userdata/players.txt");
                if (f.good()){
                    fs::remove("userdata/players_obsolete.txt");
                    fs::copy("userdata/players.txt", "userdata/players_obsolete.txt");
                }
                f.close();
                for(size_t i = 0; i < l.size(); i ++)
                {
                    if(l[i].getName() == currentProfile.getName())
                        l.erase(l.begin() + i);
                }
                l.push_back(currentProfile);
                std::ofstream g("userdata/players.txt");
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
                std::cout << "q to quit\n";
                rlutil::msleep(1000);
                std::cout << "GET READY TO TYPE.\n";
                rlutil::msleep(1000);
                std::cout << "3.\n";
                rlutil::msleep(1000);
                std::cout << "2.\n";
                rlutil::msleep(1000);
                std::cout << "1.\n";
                rlutil::msleep(400);
                std::cout << "GO!\n";
                rlutil::msleep(400);
                getline(std::cin, userInput);
                rlutil::cls();
                while(true)
                {
                    std::string s = "";

                    int totalvalue = 0;
                    int numberowords = Random::get(10,12);
                    int nonmatch = 0;

                    for(int i = 1; i <= numberowords; i ++)
                    {
                        int wordrand = Random::get(0,int(arrsize-1));
                        if(i != 1) s+= " ";
                        s = s + wl[wordrand];
                    }
                    std::cout << s << "\n";
                    getline(std::cin, userInput);
                    if(userInput == "q" || userInput == "Q" || userInput.empty())
                        break;

                    if(abs(int(s.size()) - int(userInput.size())) < 3) {
                        int nr = 0;
                        for (unsigned long long int i = 0; i < std::min(s.size(), userInput.size()); i++) {
                            if (s[i] != userInput[i])
                                nonmatch++;
                        }
                        for (char i: s) {
                            if (i != ' ') {
                                nr++;
                                totalvalue += letterVal[i - 'a'];
                            }
                        }
                        int w = int(std::max(0, numberowords * totalvalue * (100 - nonmatch * nonmatch) / 100 / nr) *
                                currentProfile.multi()) - 2 * abs(int(s.size()) - int(userInput.size()));
                        currentProfile.changeBal(w);
                        std::cout << w << "\n";
                    }
                    else {
                        std::cout << "Input length too far from given string length\n";
                        currentProfile.changeBal(0
                        );
                    }
                    rlutil::msleep(2000);
                    rlutil::cls();
                }
            }
            else if(userInput[0] == 's' || userInput[0] == 'S')
            {
                rlutil::cls();
                std::cout << "b for boosts\nf for autofarmers\n";
                std::cin >> userInput;
                if(userInput[0] == 'b' || userInput[0] == 'B')
                {
                    rlutil::cls();
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
                    rlutil::cls();
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
