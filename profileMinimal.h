//
// Created by catag on 5/18/2022.
//

#ifndef OOP_PROFILEMINIMAL_H
#define OOP_PROFILEMINIMAL_H


#include <string>
#include "boost.h"

class profileMinimal {
protected:
    std::string name;
    long long int balance;


public:
    [[maybe_unused]] virtual void changeBal(long long int x);
    [[maybe_unused]] void setName(const std::string& s);
    [[maybe_unused]] std::string getName();
    [[maybe_unused]] virtual long long int getBal();
    explicit profileMinimal(const std::string& name_= "untitled");

    profileMinimal& operator=(const profileMinimal& other);

    [[maybe_unused]] virtual float multi ();
    friend std::ostream& operator<<(std::ostream& os, const profileMinimal& p);

    [[maybe_unused]] profileMinimal(const profileMinimal& other);

    profileMinimal(const std::string &name, long long int balance);

    virtual ~profileMinimal();
    virtual char profileType();
    virtual void addBoost(const boost& b);
    virtual void print(std::ostream& os) const;


};


#endif //OOP_PROFILEMINIMAL_H
