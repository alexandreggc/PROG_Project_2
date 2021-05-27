#pragma once
#include <iostream>

using namespace std;

// clears stream buffer
void invalidInput(const string msg) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << msg << ' ';
}

// chooses the maze number
int mazeNumber() {
    int maze_number;
    cout << endl;
    cout << "Enter the maze number (1-99) or 0 to return to main menu: ";
    while (true) {
        cin >> maze_number;
        if (cin.peek() == '\n' && !cin.fail() && maze_number >= 0 && maze_number < 100) {
            break;
        }
        else if (cin.fail() && cin.eof()) exit(0);
        invalidInput("Please enter a valid maze number. ");
    }
    return maze_number;
}

// creates maze file name if file argument is 'm' and winners file name if it's 'w'
string fileString(const char file, int maze_number) {
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
double timer() {
    time_t current_time;
    double seconds;
    time(&current_time);
    seconds = difftime(current_time, 0);
    return seconds;
}
