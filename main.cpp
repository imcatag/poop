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
#include "hardcoreProfile.h"

const int arrsize = 5584;
using Random = effolkronium::random_static;
namespace fs = std::filesystem;


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

void quitGame(std::vector<std::shared_ptr<profileMinimal>>  l, const std::shared_ptr<profileMinimal> currentProfile) {
    std::ifstream f1("userdata/players.txt");
    if (f1.good()) {
        fs::remove("userdata/players_obsolete.txt");
        fs::copy("userdata/players.txt", "userdata/players_obsolete.txt");
    }
    f1.close();

    std::ifstream f2("userdata/hardcoreplayers.txt");
    if (f2.good()) {
        fs::remove("userdata/hardcoreplayers_obsolete.txt");
        fs::copy("userdata/hardcoreplayers.txt", "userdata/hardcoreplayers_obsolete.txt");
    }
    f2.close();
    for (size_t i = 0; i < l.size(); i++) {
        if (l[i]->getName() == currentProfile->getName())
            l.erase(l.begin() + i);
    }
    l.push_back(currentProfile);
    std::ofstream basicoutput("userdata/players.txt");
    std::ofstream hardcoreoutput("userdata/hardcoreplayers.txt");
    for (auto i: l) {
        std::shared_ptr profile = std::dynamic_pointer_cast<normalProfile>(i);
        //auto* profile = dynamic_pointer_cast<normalProfile*> (i);
        if (profile != nullptr) {
            basicoutput << profile->getName() << "\n";
            basicoutput << profile->getBal() << "\n";
            for (auto j: profile->getFarmers()) {
                basicoutput << j.getName() << " ";
            }
            basicoutput << "\n";
            for (auto j: profile->getCount()) {
                basicoutput << j << " ";
            }
            basicoutput << "\n";
            for (size_t j = 0; j < profile->getBoosts().size(); j++) {
                basicoutput << profile->getBoosts()[j].getName() << " " << profile->getBoosts()[j].getUses() << " ";
            }
            basicoutput << "\n";
        }
        else {
            std::shared_ptr profilehardcore = std::dynamic_pointer_cast<hardcoreProfile>(i);
            hardcoreoutput << profilehardcore->getName() << "\n" << profilehardcore->getBal() << "\n";
        }
    }
}

std::vector<std::shared_ptr<profileMinimal>> readHardcorePlayers()
{
    std::vector<std::shared_ptr<profileMinimal>>  l;
    std::ifstream testforfile("userdata/hardcoreplayers.txt");
    if(!testforfile.good())
    {
        std::cout << "no file\n";
        testforfile.close();
        std::ofstream g("userdata/hardcoreplayers.txt");
        g << "";
        g.close();
    }
    testforfile.close();
    std::ifstream f("userdata/hardcoreplayers.txt");

    long long int bal;
    std::string playerName;

    while(getline(f, playerName)) // read all playerdata file
    {
        f >> bal;
        f.get();

        hardcoreProfile aup{playerName, bal};
        l.push_back(aup.clone());

        std::cout << aup << "\n";
    }
    return l;
}

std::vector<std::shared_ptr<profileMinimal>> readBasicPlayers(std::vector<autoFarmer> farm, std::vector<boost> b)
{
    std::vector<std::shared_ptr<profileMinimal>>  l;
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


    while(getline(f, playerName)) // read all playerdata file
    {
        boostname.clear();
        boostcnt.clear();
        int spaces = 0;
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

        l.push_back(aup.clone());
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

void playCycle(std::shared_ptr<profileMinimal> currentProfile)
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
                currentProfile->changeBal(0);
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
                            currentProfile->multi()) - 2 * abs(int(s.size()) - int(userInput.size()));
                currentProfile->changeBal(w);
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

void buyCycle(std::shared_ptr<profileMinimal> currentProfile, const std::vector<boost>& b, const std::vector<autoFarmer>& farm)
{
    if(currentProfile->profileType() == 'h'){std::cout << "This is a hardcore profile. Can't go shopping."; rlutil::msleep(1200); return;}
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
                    if(currentProfile->getBal() > i.getPrice())
                    {
                        currentProfile->changeBal(-i.getPrice());
                        currentProfile->addBoost(i);
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
    std::vector<std::shared_ptr<profileMinimal>>  profileList;
//    std::vector<hardcoreProfile>  hardcorePlayers;
    std::vector<autoFarmer> farm = initfarmer();
    std::shared_ptr<profileMinimal> currentProfile;
    std::string userInput;
    bool logged = false;
    int failcount = 0;
    fs::create_directories("userdata");
    while(true)
    {
        if(!logged) // login, but there is no logout feature yet
        {
            std::cout << "Choose a profile or type \'new\' / \'new hardcore\' to create a new profile\n";
            profileList = readBasicPlayers(farm, b);
            auto profileList2 = readHardcorePlayers();
            profileList.insert(std::end(profileList), std::begin(profileList2), std::end(profileList2));
//            hardcorePlayers = readHardcorePlayers();
            while(true) // profile selection loop
            {
                if(logged) break;
                getline(std::cin, userInput);
                if(userInput == "q" || userInput == "Q") return 0;
                else if(userInput == "new") {
                    int tries = 0;
                    while (true) {
                        tries ++;
                        try {
                            std::cout << "Name your profile: ";
                            std::cin >> userInput;
                            //bool nameused = false;
                            if(userInput.length() < 2)
                                throw naming_error{"This name is too short. Give me antoher one.\n"};
                            for (auto i: profileList) {
                                if (i->getName() == userInput) {
                                    throw naming_error{"This name is already on the list. Give me antoher one.\n"};
//                                nameused = true;
                                    break;
                                }
                            }
//                        if (nameused) throw naming_error{"This name is already on the list. Give me antoher one."};
//                        if (!nameused)
//                        {
                            normalProfile aup{userInput};
                            currentProfile = aup.clone();
                            profileList.push_back(currentProfile);
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
                else if(userInput == "new hardcore") {
                    int tries = 0;
                    while (true) {
                        tries ++;
                        try {
                            std::cout << "Name your profile: ";
                            std::cin >> userInput;
                            //bool nameused = false;
                            if(userInput.length() < 2)
                                throw naming_error{"This name is too short. Give me antoher one.\n"};
                            for (auto i: profileList) {
                                if (i->getName() == userInput) {
                                    throw naming_error{"This name is already on the list. Give me antoher one.\n"};
//                                nameused = true;
                                    break;
                                }
                            }
//                        if (nameused) throw naming_error{"This name is already on the list. Give me antoher one."};
//                        if (!nameused)
//                        {
                            hardcoreProfile aup{userInput};
                            currentProfile = aup.clone();
                            profileList.push_back(currentProfile);
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
                    for(auto i : profileList)
                    {
                        if(userInput == i->getName())
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
            std::cout << "Yo. Choose an option. Playing on profile "<< currentProfile->getName() << "\n";
            mainMenu();
            std::cin >> userInput;
            if(userInput[0] == 'q' || userInput[0] == 'Q')
            {
                if(!logged) rlutil::msleep(2); // just to pass cppcheck on clang 11
                quitGame(profileList, currentProfile);
                return 0;
            }
            else if(userInput[0] == 'c' || userInput[0] == 'C')
            {
                auto aup = currentProfile;
                aup->setName("copy of " + currentProfile->getName());
                profileList.push_back(aup);
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
