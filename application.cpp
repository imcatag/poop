//
// Created by catag on 6/2/2022.
//
#ifdef _MSC_VER
    #pragma warning( disable : 4267 )
#endif

#include "application.h"
#include "normalProfile.h"
#include "hardcoreProfile.h"
#include "errors.h"
#include "randomWords.h"
#include "wordlist.h"
#include "ext/rlutil/rlutil.h"
#include <filesystem>
#include <memory>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

void application::setBoostList(const std::vector<boost>& boostList_) {
    boostList = boostList_;
}

void application::setFarmList(const std::vector<autoFarmer>& farmList_) {
    farmList = farmList_;
}

//const std::vector<boost> &application::getBoostList() const {
//    return boostList;
//}
//
//const std::vector<autoFarmer> &application::getFarmList() const {
//    return farmList;
//}

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

template <typename T>
std::string collectionToString(T col)
{
    std::stringstream ss;
    for(auto i : col)
    {
        ss << i << " ";
    }
    return ss.str();
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
            int nonmatch = 0;
            randomWords<10,12> rw;
            auto rwl = rw.getRandomWords();
            int rwnr = rwl.size();
            for (int i = 0; i < rwnr; i++) {
                if (i != 0) s += " ";
                s = s + rwl[i];
            }
            std::cout << collectionToString(rwl) << "\n";
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
                int w = int(max(0, (rwnr + 1) * totalvalue * (100 - nonmatch * nonmatch) / 100 / nr) *
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

std::vector<std::shared_ptr<profileMinimal>> application::initplayerlist() {
    auto profileList1 = readBasicPlayers();
    auto profileList2 = readHardcorePlayers();
    profileList1.insert(std::end(profileList1), std::begin(profileList2), std::end(profileList2));
    return profileList1;
}

void application::init() {
    std::cout << "Choose a profile or type \'new\' / \'new hardcore\' to create a new profile\n";
    setBoostList(initboost());
    setFarmList(initfarmer());
    setProfileList(initplayerlist());
    auto& app = application::get_app();
    std::cout << "/////////////////////QUICK LIST/////////////////////\n" << collectionToString(app.getVectorOfProfileNames()) << "\n";

}

std::vector<boost> application::initboost() {
    boost b1{"2x1k", 2000, 2, 600},
            b2{"3x1k", 1000, 3, 800},
            b3{"4x500", 500, 4, 1000};
    std::vector<boost> boostVector {b1, b2, b3};
    return boostVector;
}

std::vector<autoFarmer> application::initfarmer() {

    autoFarmer  f1{"2@300s", 300, 2},
            f2{"5@600s", 600, 5},
            f3{"12@1200s", 1200, 12};
    std::vector<autoFarmer> f{f1, f2, f3};
    return f;
}

std::vector<std::shared_ptr<profileMinimal>> application::readHardcorePlayers() {
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

std::vector<std::shared_ptr<profileMinimal>> application::readBasicPlayers(){
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
                for (const auto& i: farmList) {
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
                    for (const auto& i: boostList) {
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

        for (const auto& i: boostList) {
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

std::vector<std::string> application::getVectorOfProfileNames() {
    std::vector<std::string> s;
    for(auto i : profileList)
        s.push_back(i->getName());
    return s;
}

