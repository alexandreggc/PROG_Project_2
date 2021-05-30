//T07_G09
#include <iostream>
#include <vector>
#include "menu.h"
#include "game.h"
#include "leaderboard.h"

using namespace std;

int main(){
    Menu menu;
    while (true) {
        menu.display();
        menu.chooseOption();

        switch (menu.getOption()) {
            case 1: {
                menu.displayRules();
                break;
            }
            case 2: {
                while (true) {
                    if (menu.mazeNumber() == 0) break; // if user enter 0 return to main menu

                    menu.chooseMazeFile();
                    menu.chooseWinnersFile();

                    if (menu.validMaze()) {
                        Game game(menu.getMaze()); // create game object
                        menu.startTimer();

                        if (game.play()) { // start the game
                            menu.stopTimer();
                            cout << endl << "Congratulations! You Won!" << endl;
                            Leaderboard ldBoard(menu.getWinners()); // create leaderboard object

                            // check if winners file exist if not create one
                            if (!ldBoard.exists()) 
                                ldBoard.createFile();
                            ldBoard.addWinner(menu.getFinalTime());
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
                    if (menu.mazeNumber() == 0) break; // if user enter 0 return to main menu
                    menu.chooseWinnersFile();
                    Leaderboard ldBoard(menu.getWinners());

                    // if winners file exist then display it
                    if (ldBoard.exists())
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
