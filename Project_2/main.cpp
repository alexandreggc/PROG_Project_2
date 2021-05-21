#include <iostream>
#include <ios>
#include <limits>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

#include "game.h"

using namespace std;

// clears stream buffer
void invalid_input(const string msg) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << msg << ' ';
}

// chooses the maze number
int maze_number() {
    int maze_number;
    cout << endl;
    cout << "Enter the maze number (1-99) or 0 to return to main menu: ";
    while (true) {
        cin >> maze_number;
        if (cin.peek() == '\n' && !cin.fail() && maze_number >= 0 && maze_number < 100) {
            break;
        }
        else if (cin.fail() && cin.eof()) exit(0);
        invalid_input("Please enter a valid maze number. ");
    }
    return maze_number;
}

// creates maze file name if file argument is 'm' and winners file name if it's 'w'
string file_str(const char file, int maze_number) {
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

int main(){
    int opt;
    cout << "Welcome to Robots Game!" << endl;
    while (true) {
        // menu display
        cout << endl;
        cout << "1) Rules" << endl;
        cout << "2) Play" << endl;
        cout << "0) Exit" << endl;
        cout << endl;

        // player chooses the option
        while (true) {
            cin >> opt;
            if (cin.peek() == '\n' && !cin.fail() && (opt == 0 || opt == 1 || opt == 2)) {
                break;
            }
            else if (cin.fail() && cin.eof()) exit(0);
            invalid_input("Please enter a valid option. ");
        }

        switch (opt) {
            case 1:
                // call game rules
                break;
            case 2: {
                while (true) {
                    int mz_num = maze_number();
                    if (mz_num == 0)
                        break;

                    string maze_name = file_str('m', mz_num);
                    fstream file(maze_name);
                    if (file.is_open() && file.good()) {
                        file.close();
                        Game game = Game(maze_name); // create game object
                        game.play();
                    }
                    else {
                        cerr << "Maze file not found!" << endl;
                    }
                }
                break;
            }
            case 0:
                exit(0); // exit game
            default:
                break;
        }
    }
}