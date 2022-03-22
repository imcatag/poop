#ifndef OOP_AUTOFARMER_H
#define OOP_AUTOFARMER_H


#include <string>
#include <ostream>
#include <ctime>

class autoFarmer
{
    std::string name;
    int timeInterval;
    int reward;
public:
    autoFarmer(const std::string& name_ = std::to_string(int(time(NULL))), int timeInterval_ = 2048, int reward_ = 0);
    std::string getName() const
    {
        return name;
    }
    /*[[maybe_unused]] int getTime() const
    {
        return timeInterval;
    }*/

    /*[[maybe_unused]] int getReward() const
    {
        return reward;
    }*/
    friend std::ostream& operator<<(std::ostream& os, const autoFarmer& p);

    ~autoFarmer();

};


#endif //OOP_AUTOFARMER_H
