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
#include "application.h"


using Random = effolkronium::random_static;
namespace fs = std::filesystem;


void mainMenu()
{
    std::cout << "\np to play\ns for shop\nc to create a copy of current profile\nq to save and quit\n";
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
std::vector<std::shared_ptr<profileMinimal>> readBasicPlayers(const std::vector<autoFarmer>& farm, const std::vector<boost>& b)
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
                for (const auto& i: farm) {
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
                    for (const auto& i: b) {
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

        for (const auto& i: b) {
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

        normalProfile aup {playerName, bal, farmers, count, boosts};

        l.push_back(aup.clone());
        std::cout << aup << "\n";

    }
    f.close();
    return l;
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
std::vector<std::shared_ptr<profileMinimal>> initplayerlist()
{
    auto& app = application::get_app();
    auto profileList = readBasicPlayers(app.getFarmList(), app.getBoostList());
    auto profileList2 = readHardcorePlayers();
    profileList.insert(std::end(profileList), std::begin(profileList2), std::end(profileList2));
    return profileList;
}

int main()
{
    auto& app = application::get_app();
    app.setBoostList(initboost());
    app.setFarmList(initfarmer());
    std::string userInput;
    bool logged = false;
    int failcount = 0;
    fs::create_directories("userdata");
    while(true)
    {
        if(!logged) // login, but there is no logout feature yet
        {
            std::cout << "Choose a profile or type \'new\' / \'new hardcore\' to create a new profile\n";
            app.setProfileList(initplayerlist());
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
                            for (auto i: app.getProfileList()) {
                                if (i->getName() == userInput) {
                                    throw naming_error{"This name is already on the list. Give me antoher one.\n"};
//                                nameused = true;
                                    break;
                                }
                            }
                            normalProfile aup{userInput};
                            app.setCurrentProfile(aup.clone());
                            app.addToProfileList(aup.clone());
                            logged = true;
                            break;
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
                            for (auto i: app.getProfileList()) {
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
                            app.setCurrentProfile(aup.clone());
                            app.addToProfileList(aup.clone());
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
                    for(auto i : app.getProfileList())
                    {
                        if(userInput == i->getName())
                        {
                            matching = true;
                            app.setCurrentProfile(i);
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
            std::cout << "Yo. Choose an option. Playing on profile "<< app.getCurrentProfile()->getName() << "\n";
            mainMenu();
            std::cin >> userInput;
            if(userInput[0] == 'q' || userInput[0] == 'Q')
            {
                if(!logged) rlutil::msleep(2); // just to pass cppcheck on clang 11
                app.quitGame();
                return 0;
            }
            else if(userInput[0] == 'c' || userInput[0] == 'C')
            {
                auto aup = app.getCurrentProfile()->clone();
                aup->setName("copy of " + app.getCurrentProfile()->getName());
                app.addToProfileList(aup);
            }
            else if(userInput[0] == 'p' || userInput[0] == 'P') // play cycle
            {
                getReady();
                app.playCycle();
            }
            else if(userInput[0] == 's' || userInput[0] == 'S')
            {
                try{
                    app.buyCycle();
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

