#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "winner.h"

#include <vector>
#include <string>

class Leaderboard {
    public:
        Leaderboard(const std::string filename);
        void display() const;
        void createFile() const;
        bool exists() const;
        void addWinner(const int time);
    private:
        void updateFile();
        void buildWinners();
        void sortWinners();
        void buildFile();
        std::string winnerName();
        bool emptyName(std::string name);
    private:
        // maximum values for name and time string size
        const int NAME_BEG = 0, NAME_SIZE = 15, TIME_BEG = 18, TIME_SIZE = 4;
        std::string filename;
        std::vector<Winner> winners;
};

#endif
