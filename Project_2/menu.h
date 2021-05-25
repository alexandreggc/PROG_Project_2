#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Menu {
    public:
        Menu();
        void display() const;
        void chooseOption();
        void chooseWinnersFile();
        void chooseMazeFile();
        void displayRules();
        bool validMaze();
        int mazeNumber();
        void startTimer();
        void stopTimer();
        std::string getWinners() const;
        std::string getMaze() const;
        int getOption() const;
        int getFinalTime() const;
    private:
        void invalidInput(const std::string msg);
        int waitForKeys(const std::vector<int>& keys);
        double timer();
        bool sameKey(const int keyIN, const std::vector<int>& keys);
        std::string fileString(const char file, int maze_number);
    private:
        std::string maze;
        std::string winners;
        int option;
        int mazenumber;
        double startTime;
        double finalTime;
};

