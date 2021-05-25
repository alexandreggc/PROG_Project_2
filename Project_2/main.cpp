#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "menuFunc.h"
#include "game.h"
#include "leaderboard.h"

using namespace std;

int main(){
    int opt;
    cout << "Welcome to Robots Game!" << endl;
    while (true) {
        // menu display
        cout << endl;
        cout << "1) Rules" << endl;
        cout << "2) Play" << endl;
        cout << "3) Winners" << endl;
        cout << "0) Exit" << endl;
        cout << endl;

        // player chooses the option
        while (true) {
            cin >> opt;
            if (cin.peek() == '\n' && !cin.fail() && (opt == 0 || opt == 1 || opt == 2 || opt == 3)) {
                break;
            }
            else if (cin.fail() && cin.eof()) exit(0);
            invalidInput("Please enter a valid option. ");
        }

        switch (opt) {
            case 1:
                // call game rules
                break;
            case 2: {
                while (true) {
                    int mzNum = mazeNumber();
                    if (mzNum == 0) break;

                    string mazeName = fileString('m', mzNum); // create the file name of the maze file
                    string winnerFilename = fileString('w', mzNum); // create the file name of the winners file
                    fstream file(mazeName);

                    if (file.is_open() && file.good()) { // if file exists then start the game
                        file.close();

                        Game game = Game(mazeName); // create game object
                        double startTime = timer();

                        if (game.play()) {
                            cout << endl << "Congratulations! You Won!" << endl;
                            double finalTime = difftime(timer(), startTime); // stop timer and store the time
                            Leaderboard ldBoard(winnerFilename); // create leaderboard object
                            
                            if (!ldBoard.exists()) // check if winners file exist if not create one
                                ldBoard.createFile();
                            ldBoard.addWinner((int)finalTime);
                            ldBoard.display();
                        }
                        else {
                            cout << "You Lost!" << endl;
                        }
                        break;
                    }
                    else {
                        cerr << "Maze file not found!" << endl;
                    }
                }
                break;
            }
            case 3:
                while (true) {
                    int mzNum = mazeNumber();
                    if (mzNum == 0) break;
                    string winnersFilename = fileString('w', mzNum);
                    Leaderboard ldBoard(winnersFilename);

                    if (ldBoard.exists()) // if winners file exist then display it
                        ldBoard.display();
                    else
                        cout << endl << "Empty list." << endl;
                    break;
                }
                break;
            case 0:
                exit(0); // exit game
            default:
                break;
        }
    }
}
