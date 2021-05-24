#pragma once
#ifndef WINNER_H_INCLUDED
#define WINNER_H_INCLUDED

#include "structs.h"
#include <string>

class Winner {
    public:
        Winner(std::string name, double time);
        std::string getName();
        double getTime();
        void setName(string Name);
        void setTime(double Time);
    private:
        std::string name;
        double time;
};



#endif // WINNER_H_INCLUDED
