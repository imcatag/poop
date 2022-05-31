//warning happens in rlutil, so I disable it
#ifdef _MSC_VER
    #pragma warning( disable : 4267 )
#endif

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <cstdlib>
#include "ext/random.hpp"
#include "boost.h"
#include "autoFarmer.h"
#include "normalProfile.h"
#include "wordlist.h"
#include "errors.h"
#include "ext/rlutil/rlutil.h"
#include "profileMinimal.h"

const int arrsize = 5584;
using Random = effolkronium::random_static;
namespace fs = std::filesystem;


//
//class demoProfile : public normalProfile{
//    enum profileTypes {basic, hardcore, demo};
//    profileTypes profileType = demo;
//public:
//
//};

void mainMenu()
{
    std::cout << "\np to play\ns for shop\nc to create a copy of current profile\nq to save and quit\n";
}

std::vector<boost> initboost() {
    std::vector<boost> boostVector;
    boost b1{"2x1k", 2000, 2, 600},
            b2{"3x1k", 1000, 3, 800},
            b3{"4x500", 500, 4, 1000};
    boostVector.push_back(b1);
    boostVector.push_back(b2);
    boostVector.push_back(b3);
    return boostVector;
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

void quitGame(std::vector<normalProfile>  l, normalProfile currentProfile) {
    std::ifstream f("userdata/players.txt");
    if (f.good()) {
        fs::remove("userdata/players_obsolete.txt");
        fs::copy("userdata/players.txt", "userdata/players_obsolete.txt");
    }
    f.close();
    for (size_t i = 0; i < l.size(); i++) {
        if (l[i].getName() == currentProfile.getName())
            l.erase(l.begin() + i);
    }
    l.push_back(currentProfile);
    std::ofstream g("userdata/players.txt");
    for (auto i: l) {
        g << i.getName() << "\n";
        g << i.getBal() << "\n";
        for (auto j: i.getFarmers()) {
            g << j.getName() << " ";
        }
        g << "\n";
        for (auto j: i.getCount()) {
            g << j << " ";
        }
        g << "\n";
        for (size_t j = 0; j < i.getBoosts().size(); j++) {
            g << i.getBoosts()[j].getName() << " " << i.getBoosts()[j].getUses() << " ";
        }
        g << "\n";

    }
}

//std::vector<hardcoreProfile> readHardcorePlayers()
//{
//    std::vector<hardcoreProfile> l;
//    std::ifstream testforfile("userdata/hardcoreplayers.txt");
//    if(!testforfile.good())
//    {
//        std::cout << "no file\n";
//        testforfile.close();
//        std::ofstream g("userdata/players.txt");
//        g << "";
//        g.close();
//    }
//    testforfile.close();
//    std::ifstream f("userdata/hardcoreplayers.txt");
//    std::string playerName;
//    long long int bal;
//    while(getline(f, playerName))
//    {
//        f >> bal;
//
//    }
//}

std::vector<normalProfile> readBasicPlayers(std::vector<autoFarmer> farm, std::vector<boost> b)
{
    std::vector<normalProfile>  l;
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

    long long int bal;

    std::vector<autoFarmer> farmers;
    std::vector<int> count;

    std::deque<boost> boosts;
    std::string boostname, boostcnt, farmername, line, playerName, cnt;

    int spaces;
    while(getline(f, playerName)) // read all playerdata file
    {
        boostname.clear();
        boostcnt.clear();
        spaces = 0;
        farmers.clear();
        count.clear();
        boosts.clear();
        f >> bal;
        f.get();
        getline(f, line);

        for(auto letter : line){
            if(letter == ' ') {
                for (auto i: farm) {
                    bool matching = true;
                    for (size_t j = 0; j < i.getName().size(); j++)
                        if (i.getName()[j] != farmername[j]) {
                            matching = false;
                            break;
                        }
                    if (matching) {
                        farmers.push_back(i);
                    }
                }
                farmername.clear();
            }
            else
                farmername += letter;

        }

        getline(f, line);

        for(auto letter : line){
            if(letter == ' ') {
                count.push_back(stoi(cnt));
                cnt.clear();
            }
            else
                cnt += letter;

        }


        getline(f, line);

        for(auto letter : line){
            if(letter == ' ') {
                spaces ++;
                if(spaces % 2 == 0) {
                    for (auto i: b) {
                        bool matching = true;
                        for (size_t j = 0; j < i.getName().size(); j++)
                            if (i.getName()[j] != boostname[j]) {
                                matching = false;
                                break;
                            }
                        if (matching) {
                            boost aub{boostname, stoi(boostcnt), i.getMultiplier(), i.getPrice()};
                            boosts.push_back(aub);
                        }
                    }
                    boostname.clear();
                    boostcnt.clear();
                }
            }
            else
            {
                if(spaces % 2 == 0)
                    boostname += letter;
                else
                    boostcnt += letter;
            }


        }

        normalProfile aup {playerName, bal, farmers, count, boosts};

        l.push_back(aup);
        std::cout << aup << "\n";
    }
    f.close();
    return l;
}

void getReady()
{
    std::string temp1;
    std::cout << "q to quit\n";
    rlutil::msleep(600);
    std::cout << "GET READY TO TYPE.\n";
    rlutil::msleep(600);
    std::cout << "3.\n";
    rlutil::msleep(600);
    std::cout << "2.\n";
    rlutil::msleep(600);
    std::cout << "1.\n";
    rlutil::msleep(400);
    std::cout << "GO!\n";
    rlutil::msleep(400);
    getline(std::cin, temp1);
    rlutil::cls();
}

void playCycle(normalProfile& currentProfile)
{
    const int letterVal[] = {1, 3, 3, 2, 1, 4,
                             2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10,
                             1, 1, 1, 1, 4, 4, 8, 4, 10}; // from scrabble, idk if accurate
    while(true)
    {
        try {
            std::string s = "", userInput = "";

            int totalvalue = 0;
            int numberowords = Random::get(10, 12);
            int nonmatch = 0;

            for (int i = 1; i <= numberowords; i++) {
                int wordrand = Random::get(0, int(arrsize - 1));
                if (i != 1) s += " ";
                s = s + wl[wordrand];
            }
            std::cout << s << "\n";
            getline(std::cin, userInput);
            if (userInput == "q" || userInput == "Q" || userInput.empty())
                break;

            if (abs(int(s.size()) - int(userInput.size())) > 3) {
                currentProfile.changeBal(0);
                throw typing_error{"\nInvalid input length! Booster use consumed if you had a booster on.\n"};
            } else {
                using namespace std;
                int nr = 0;
                for (unsigned long long int i = 0; i < min(s.size(), userInput.size()); i++) {
                    if (s[i] != userInput[i])
                        nonmatch++;
                }
                for (char i: s) {
                    if (i != ' ') {
                        nr++;
                        totalvalue += letterVal[i - 'a'];
                    }
                }
                int w = int(max(0, numberowords * totalvalue * (100 - nonmatch * nonmatch) / 100 / nr) *
                            currentProfile.multi()) - 2 * abs(int(s.size()) - int(userInput.size()));
                currentProfile.changeBal(w);
                std::cout << w << "\n";
            }
            rlutil::msleep(1200);
            rlutil::cls();
        }
        catch(typing_error& err)
        {
            std::cout << err.what();
            rlutil::msleep(1200);
            rlutil::cls();
        }
    }
}

void buyCycle(normalProfile& currentProfile, const std::vector<boost>& b, const std::vector<autoFarmer>& farm)
{
    std::string userInput = "";

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
            return;
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
                        throw shop_error {"Not enough balance!"};

                    }
                    found = true;
                }
            }
            if(!found)
            {
                throw shop_error{"Couldn't find that!"};
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
        std::cout << "This is totally implemented. Returning you to the menu.\n";
        rlutil::msleep(2500);
    }
}

int main()
{
    std::vector<boost> b = initboost();
    std::vector<normalProfile>  basicPlayers;
//    std::vector<hardcoreProfile>  hardcorePlayers;
    std::vector<autoFarmer> farm = initfarmer();
    normalProfile currentProfile;
    std::string userInput;
    bool logged = false;
    int failcount = 0;
    fs::create_directories("userdata");
    while(true)
    {
        if(!logged) // login, but there is no logout feature yet
        {
            std::cout << "Choose a profile or type \'new\' to create a new profile\n";
            basicPlayers = readBasicPlayers(farm, b);
//            hardcorePlayers = readHardcorePlayers();
            while(true) // profile selection loop
            {
                if(logged) break;
                std::cin >> userInput;
                if(userInput == "q" || userInput == "Q") return 0;
                else if(userInput == "new") {
                    int tries = 0;
                    while (true) {
                        tries ++;
                        try {
                            std::cout << "Name your profile: ";
                            std::cin >> userInput;
                            //bool nameused = false;
                            for (auto i: basicPlayers) {
                                if (i.getName() == userInput) {
                                    throw naming_error{"This name is already on the list. Give me antoher one.\n"};
//                                nameused = true;
                                    break;
                                }
                            }
//                        if (nameused) throw naming_error{"This name is already on the list. Give me antoher one."};
//                        if (!nameused)
//                        {
                            normalProfile aup{userInput};
                            currentProfile = aup;
                            basicPlayers.push_back(currentProfile);
                            logged = true;
                            break;
//                        }
                        }
                        catch (app_error &err) {
                            if (tries > 5) {std::cout << "You're obviously not here to create a new profile so I'm going. Bye!"; return 0;}

                            std::cout << err.what();

                        }
                    }
                }
                else
                {

                    bool matching = false;
                    for(auto i : basicPlayers)
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
        while(true) // most user interaction happens here
        {
            rlutil::cls();
            std::cout << "Yo. Choose an option. Playing on profile "<< currentProfile.getName() << "\n";
            mainMenu();
            std::cin >> userInput;
            if(userInput[0] == 'q' || userInput[0] == 'Q')
            {
                if(!logged) rlutil::msleep(2); // just to pass cppcheck on clang 11
                quitGame(basicPlayers, currentProfile);
                return 0;
            }
            else if(userInput[0] == 'c' || userInput[0] == 'C')
            {
                normalProfile aup = currentProfile;
                aup.setName("copy of " + currentProfile.getName());
                basicPlayers.push_back(aup);
            }
            else if(userInput[0] == 'p' || userInput[0] == 'P') // play cycle
            {
                getReady();
                playCycle(currentProfile);
            }
            else if(userInput[0] == 's' || userInput[0] == 'S')
            {
                try{
                    buyCycle(currentProfile, b, farm);
                }
                catch(shop_error& err)
                {
                    std::cout << "\n" << err.what() << "\n";
                    rlutil::msleep(1000);
                }
            }
            else {std::cout << "No clue what you're trying to do."; return 0;}
        }

        break;
    }

    return 0;
}
