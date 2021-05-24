#include "leaderboard.h"
#include "structs.h"
#include "winner.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

Leaderboard::Leaderboard(double final_time, const string& filename) {
    this->final_time = final_time;
    winners_filename = filename;
}

void Leaderboard::showLeaderboard(){

    winners_file();
    new_winner();
    file_to_vectors();
    sort_winners();
    del_duplicate();
    vectors_to_file();
    ifstream file(winners_filename);
    cout << endl << file.rdbuf() << endl;  // displays leaderboard in console
    file.close();
}

void Leaderboard::winners_file(const string filename) {
    fstream file(filename.c_str());
    if (file.is_open() && file.good() == true) { // checks if the file already exists
        file.close();
        return;
    }
    else {
        file.close();
        ofstream f{ filename };  // creates leaderboard file if it doesn't exist
        fstream file(filename.c_str());
        file << "Player          - Time\n";
        file << "----------------------\n";
        file.close();
    }
}

string Leaderboard::winner_name() {
    string name;
    cout << endl << "Congratulations, you won!" << endl;
    cout << "What's your name (15 characters maximum)? ";
    cin.ignore(10000, '\n');
    while (true) {
        cin.clear();
        getline(cin, name, '\n');
        if (!cin.fail() && name.size() <= 15) {
            break;
        }
        else if (cin.fail() && cin.eof()) exit(0);
        cout << "Please enter a valid name. ";
    }
    return name;
}

void Leaderboard::new_winner() {
    stringstream winner_s, final_time_s;
    winner = Winner(winner_name(), final_time);

    ofstream file(winners_filename, fstream::app);
    winner_s << left << setfill(' ') << setw(15) << winner.getName();
    final_time_s << setfill(' ') << setw(4) << to_string((int)winner.getTime());
    file << winner_s.str() << " - " << final_time_s.str() << "\n";
    file.close();
}

void Leaderboard::file_to_vectors() {
    const int NAME_BEG = 0, NAME_SIZE = 15, TIME_BEG = 18, TIME_SIZE = 4;
    string line, name, time;
    ifstream file(winners_filename);

    file.seekg(ios::beg);
    for (int i = 0; i < 2; i++)
        file.ignore(10000, '\n');
    while (true) {
        file.clear();
        getline(file, line, '\n');
        if (file.eof()) break;
        winner.setName(line.substr(NAME_BEG, NAME_SIZE));
        winner.setTime(stoi(line.substr(TIME_BEG, TIME_SIZE)));
        winners.push_back(winner);
    }
    file.close();
}

string Leaderboard::cmp_names(const string name1,const string name2) {
    for (unsigned int i = 0; i < name1.size(); i++) {
        if (int(name1[i]) < int(name2[i]))
            return name1;
        else if (int(name1[i]) > int(name2[i]))
            return name2;
    }
    return name2;
}

void Leaderboard::switch_pos(int i) {
    Winner w = winners.at(i);
    winners.at(i) = winners.at(i + 1);
    winners.at(i + 1) = w;
}

void Leaderboard::sort_winners() {
    bool not_done = true;
    while (not_done) {
        not_done = false;
        for (int i = 0; i < winners.size() - 1; i++) {
            string name = cmp_names(winners.at(i).getName(), winners.at(i + 1).getName());
            if (winners.at(i).getTime() > winners.at(i + 1).getTime()) {
                not_done = true;
                switch_pos(winners, i);
            }
            if (winners.at(i).getTime() == winners.at(i + 1).getTime() && winners.at(i).getName() != name) {
                not_done = true;
                switch_pos(winners, i);
            }
        }
    }
}

void Leaderboard::del_duplicate() {
    int i = 0;
    while (i < winners.size()) {
        for (int j = i + 1; j <= winners.size() - 1; j++) {
            if (winners.at(i).getName() == winners.at(j).getName()) {
                if (winners.at(i).getTime() > winners.at(j).getTime()) {
                    winners.erase(winners.begin() + i);
                }
                else {
                    winners.erase(winners.begin() + j);
                }
            }
        }
        i += 1;
    }
}

void Leaderboard::vectors_to_file() {
    ofstream file(winners_filename, ofstream::trunc);
    file << "Player          - Time\n";
    file << "----------------------\n";
    for (int i = 0; i < winners.size(); i++) {
        stringstream winner_s, time_s;
        winner_s << left << setfill(' ') << setw(15) << winners.at(i).getName();
        time_s << setfill(' ') << setw(4) << to_string(winners.at(i).getTime());
        file << winner_s.str() << " - " << time_s.str() << "\n";
    }
    file.close();
}


