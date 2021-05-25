#include "menu.h"

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Menu::Menu() {
    cout << "Welcome to Robots Game!" << endl;
    option = NULL;
    mazenumber = NULL;
    startTime = NULL;
    finalTime = NULL;
}

void Menu::display() const {
    cout << endl;
    cout << "1) Rules" << endl;
    cout << "2) Play" << endl;
    cout << "3) Winners" << endl;
    cout << "0) Exit" << endl;
    cout << endl;
}

void Menu::chooseOption() {
    vector<int> options = {0, 1, 2, 3};
    option = waitForKeys(options);
}

// create the file name of the winners file
void Menu::chooseWinnersFile() {
    winners = fileString('w', mazenumber);
}

// create the file name of the maze file
void Menu::chooseMazeFile() {
    maze = fileString('m', mazenumber);
}

// display game rules text file
void Menu::displayRules() {
    fstream rules("rules.txt");
    cout << endl << rules.rdbuf() << ' ';
    rules.close();
    vector<int> keys{ 0 };
    waitForKeys(keys);
}

// if maze file exists then start the game
bool Menu::validMaze() {
    string mazeName = fileString('m', mazenumber);
    fstream file(mazeName);
    if (file.is_open() && file.good()) {
        file.close();
        return true;
    }
    return false;
}

// wait for thw user to enter any of the specified keys
int Menu::waitForKeys(const vector<int>& keys) {
    int key;
    while (true) {
        cin >> key;
        if (cin.peek() == '\n' && !cin.fail() && sameKey(key, keys)) {
            break;
        }
        else if (cin.fail() && cin.eof()) exit(0);
        invalidInput("Please enter a valid option. ");
    }
    return key;
}

// clears stream buffer
void Menu::invalidInput(const string msg) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << msg << ' ';
}

// chooses the maze number
int Menu::mazeNumber() {
    int mzNum;
    cout << endl;
    cout << "Enter the maze number (1-99) or 0 to return to main menu: ";
    while (true) {
        cin >> mzNum;
        if (cin.peek() == '\n' && !cin.fail() && mzNum >= 0 && mzNum < 100) {
            break;
        }
        else if (cin.fail() && cin.eof()) exit(0);
        invalidInput("Please enter a valid maze number. ");
    }
    mazenumber = mzNum;
    return mzNum;
}

void Menu::startTimer() {
    startTime = timer();
}

// stop timer and store the time
void Menu::stopTimer() { 
    finalTime = difftime(timer(), startTime);
}

std::string Menu::getWinners() const {
    return winners;
}

std::string Menu::getMaze() const {
    return maze;
}

int Menu::getOption() const {
    return option;
}

int Menu::getFinalTime() const {
    return (int) finalTime;
}

// creates maze file name if file argument is 'm' and winners file name if it's 'w'
string Menu::fileString(const char file, int maze_number) {
    string filename;
    stringstream file_number;
    if (maze_number == 0)
        return "exit";
    filename = to_string(maze_number);
    file_number << setfill('0') << setw(2) << filename;
    if (file == 'm')
        filename = "MAZE_" + file_number.str();
    else if (file == 'w')
        filename = "MAZE_" + file_number.str() + "_WINNERS";
    return filename + ".txt";
}

// count the time in seconds
double Menu::timer() {
    time_t current_time;
    double seconds;
    time(&current_time);
    seconds = difftime(current_time, 0);
    return seconds;
}

// check if some key is in keys vector
bool Menu::sameKey(const int keyIN, const vector<int>& keys) {
    for (int key : keys) {
        if (key == keyIN)
            return true;
    }
    return false;
}

