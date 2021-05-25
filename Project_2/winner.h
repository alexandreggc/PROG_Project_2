#pragma once
#ifndef WINNER_H
#define WINNER_H

#include <string>

class Winner {
    public:
        Winner(std::string name, int time);
        std::string getName();
        int getTime();
        void setTime(int time);
        bool operator<(const Winner& winner);
    private:
        std::string name;
        int time;
};

#endif
