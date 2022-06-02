//
// Created by catag on 6/2/2022.
//
#ifdef _MSC_VER
    #pragma warning( disable : 4267 )
#endif

#include "application.h"
#include "normalProfile.h"
#include "hardcoreProfile.h"
#include "ext/random.hpp"
#include "errors.h"
#include "wordlist.h"
#include "ext/rlutil/rlutil.h"
#include <filesystem>
#include <memory>
#include <fstream>

namespace fs = std::filesystem;
using Random = effolkronium::random_static;

void application::setBoostList(const std::vector<boost>& boostList_) {
    boostList = boostList_;
}

void application::setFarmList(const std::vector<autoFarmer>& farmList_) {
    farmList = farmList_;
}

const std::vector<boost> &application::getBoostList() const {
    return boostList;
}

const std::vector<autoFarmer> &application::getFarmList() const {
    return farmList;
}

const std::vector<std::shared_ptr<profileMinimal>> &application::getProfileList() const {
    return profileList;
}

void application::setProfileList(const std::vector<std::shared_ptr<profileMinimal>>& profileList_) {
    profileList = profileList_;
}

const std::shared_ptr<profileMinimal> &application::getCurrentProfile() const {
    return currentProfile;
}

void application::setCurrentProfile(std::shared_ptr<profileMinimal> currentProfile_) {
    currentProfile = currentProfile_;
}

void application::addToProfileList(std::shared_ptr<profileMinimal> profile) {
    profileList.push_back(profile->clone());
}

application &application::get_app() {
    static application app;
    return app;
}

void application::quitGame() {
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
    for (size_t i = 0; i < profileList.size(); i++) {
        if (profileList[i]->getName() == currentProfile->getName())
            profileList.erase(profileList.begin() + i);
    }
    profileList.push_back(currentProfile);
    std::ofstream basicoutput("userdata/players.txt");
    std::ofstream hardcoreoutput("userdata/hardcoreplayers.txt");
    for (const auto& i: profileList) {
        std::shared_ptr profile = std::dynamic_pointer_cast<normalProfile>(i);
        if (profile != nullptr) {
            normalProfile_decorator dec {*profile};
            basicoutput << dec;
        }
        else {
            std::shared_ptr profilehardcore = std::dynamic_pointer_cast<hardcoreProfile>(i);
            hardcoreProfile_decorator dec {*profilehardcore};
            hardcoreoutput << dec;
        }
    }
}

void application::playCycle() {
    const int letterVal[] = {1, 3, 3, 2, 1, 4,
                             2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10,
                             1, 1, 1, 1, 4, 4, 8, 4, 10}; // from scrabble, idk if accurate
    while(true)
    {
        try {
            std::string s, userInput;

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

void application::buyCycle() {
    if(!currentProfile->canUseShop()){std::cout << "This is a hardcore profile. Can't go shopping."; rlutil::msleep(1200); return;}
    std::string userInput;

    rlutil::cls();
    std::cout << "b for boosts\nf for autofarmers\n";
    std::cin >> userInput;
    if(userInput[0] == 'b' || userInput[0] == 'B')
    {
        rlutil::cls();
        for(const auto& i : boostList)
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
            for(const auto& i : boostList)
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
        for(const auto& i : farmList)
        {
            std::cout << i << "\n";
        }
        std::cout << "This is totally implemented. Returning you to the menu.\n";
        rlutil::msleep(2500);
    }
}

