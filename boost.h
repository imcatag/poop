#ifndef OOP_BOOST_H
#define OOP_BOOST_H


#include <string>
#include <ostream>
#include <ctime>

class boost
{
    std::string name;
    int uses;
    int price;
    float multiplier;
public:
    explicit boost (const std::string& name_ = std::to_string(int(time(NULL))), int uses_ = 1000, float multiplier_ = 2, int price_ = 300);

    void decBoost();
    std::string getName() const;
    float getMultiplier() const;
    int getUses() const;
    int getPrice() const;
    friend std::ostream& operator<<(std::ostream& os, const boost& p);

    virtual ~boost();
};

#endif //OOP_BOOST_H
