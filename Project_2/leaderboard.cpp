#include "leaderboard.h"
#include "winner.h"

#include <ios>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

Leaderboard::Leaderboard(const string filename) {
    this->filename = filename.c_str();
}

// displays leaderboard in console
void Leaderboard::display() const {
    ifstream file(filename);
    cout << endl << file.rdbuf() << endl;
    file.close();
}

// creates leaderboard file 
void Leaderboard::createFile() const {
    ofstream f{ filename };
}

// returns true if file exists or false if not
bool Leaderboard::exists() const {
    fstream file(filename);
    if (file.is_open() && file.good()) {
        file.close();
        return true;
    }
    return false;
}

// adds a winner to the winners vector
void Leaderboard::addWinner(const int time) {
    buildWinners();
    string name = winnerName();
    for (Winner &winner : winners) {
        if (winner.getName() == name) {
            if (time < winner.getTime()) {
                winner.setTime(time);
                updateFile();
            }
            return;
        }
    }
    Winner winner(name, time);
    winners.push_back(winner);
    updateFile();
}

// update the winners file with new and sorted winners
void Leaderboard::updateFile() {
    sortWinners();
    buildFile();
}

// download winners from winners file to winners vector
void Leaderboard::buildWinners() {
    int time;
    string line, name;
    ifstream file(filename);

    file.seekg(ios::beg);
    for (int i = 0; i < 2; i++)
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        file.clear();
        getline(file, line, '\n');
        if (file.eof()) break;

        // gets the substring of a file line containing the winner name
        name = line.substr(NAME_BEG, NAME_SIZE);

        // gets the substring of a file line containing the winner time and converts it to integer
        time = stoi(line.substr(TIME_BEG, TIME_SIZE));

        Winner winner(name, time);
        winners.push_back(winner); // add file winners to winners vector
    }
    file.close();
}

// sort winners file by name and time order
void Leaderboard::sortWinners() {
    sort(winners.begin(), winners.begin() + winners.size());
}

// upload winners from winners vector to the the winners file 
void Leaderboard::buildFile() {
    ofstream file(filename, ofstream::trunc);
    file << "Player          - Time\n";
    file << "----------------------\n";
    for (Winner winner : winners) {
        stringstream winner_s, time_s;
        // adjust text in proper format to upload to file
        winner_s << left << setfill(' ') << setw(NAME_SIZE) << winner.getName();
        time_s << setfill(' ') << setw(TIME_SIZE) << to_string(winner.getTime());
        file << winner_s.str() << " - " << time_s.str() << "\n";
    }
    file.close();
}

// ask the winner's name and returns it
string Leaderboard::winnerName() {
    string name;
    cout << endl << "What's your name (15 characters maximum)? ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cin.clear();
        getline(cin, name, '\n');
        if (!cin.fail() && 0 < name.size() && name.size() <= 15 && !emptyName(name)) {
            break;
        }
        else if (cin.fail() && cin.eof()) exit(0);
        cout << "Please enter a valid name. ";
    }
    stringstream nameS;
    nameS << left << setfill(' ') << setw(NAME_SIZE) << name;
    return nameS.str();
}

// return true is name is empty
bool Leaderboard::emptyName(string name) {
    int cnt = 0;
    for (size_t i = 0; i < name.size(); i++) {
        if (isspace(name[i])) cnt++;
    }
    return (int)name.size()==cnt;
}