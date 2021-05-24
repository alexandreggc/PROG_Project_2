#pragma once
#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "structs.h"
#include "winner.h"

using namespace std;

class Leaderboard {
    public:
        Leaderboard(double final_time, const string& filename);
        void showLeaderboard();
    private:
        void winners_file();
        void new_winner();
        void file_to_vectors();
        void sort_winners();
        void del_duplicate();
        void vectors_to_file();
        string winner_name();
        string cmp_names(const string name1,const string name2);
        void switch_pos(vector<NameAndTime>& winners, int i);
    private:
        double final_time;
        string winners_filename;
        vector<Winner> winners;
        Winner winner;

};


#endif // LEADERBOARD_H_INCLUDED
