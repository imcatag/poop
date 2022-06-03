#ifndef OOP_WORDLIST_H
#define OOP_WORDLIST_H

#include <vector>
#include <string>

class wordlist {
private:
    wordlist() = default;
    std::vector<std::string> wl;
    int arrsize = 5584;
public:
    void init();
    wordlist(const wordlist&) = delete;
    wordlist& operator=(const wordlist&) = delete;
    static wordlist& get_wordlist();

    std::vector<std::string> getWordList();
    [[nodiscard]] int getArrsize() const;
};

#endif //OOP_WORDLIST_H
