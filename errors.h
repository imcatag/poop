//
// Created by catag on 5/18/2022.
//

#ifndef OOP_ERRORS_H
#define OOP_ERRORS_H


#include <stdexcept>

class app_error : public std::runtime_error {
public:
    explicit app_error(const std::string &arg) : runtime_error(arg) {}
};

class typing_error : public app_error {
public:
    explicit typing_error(const std::string &arg) : app_error(arg) {}
};

class shop_error : public app_error {
public:
    explicit shop_error(const std::string &arg) : app_error(arg) {}
};

class naming_error : public app_error {
public:
    explicit naming_error(const std::string &arg) : app_error(arg) {}
};


#endif //OOP_ERRORS_H
