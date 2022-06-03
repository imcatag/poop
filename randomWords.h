//
// Created by catag on 6/3/2022.
//

#ifndef OOP_RANDOMWORDS_H
#define OOP_RANDOMWORDS_H


#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include "wordlist.h"
#include "ext/random.hpp"
#include "profileMinimal.h"



template<int T, int U>
class randomWords{
private:
    const int minNumberOfWords = T;
    const int maxNumberOfWords = U;
public:
    std::vector<std::string> getRandomWords(){
        using Random = effolkronium::random_static;

        auto& wl = wordlist::get_wordlist();

        std::vector<std::string> s;
        int numberOfWords = Random::get(T,U);

        for (int i = 1; i <= numberOfWords; i++) {
            s.push_back(wl.getWordList()[Random::get(0, int(wl.getArrsize() - 1))]);
        }

        return s;
    };
};




#endif //OOP_RANDOMWORDS_H
