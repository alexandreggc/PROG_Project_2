#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

Game::Game(const string& filename) {
    file.open(filename);
    int rows, cols, count=0;
    char c;
    file >> rows >> c >> cols >> c;  // get number os rows and columns of the maze
    maze = Maze(rows, cols);
    //file.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            file.get(c);
            if (c == '*' || c == '+') { // add posts to maze object
                Post p = Post(row, col, c);
                maze.addPost(p);
            }
            else if (c == 'H') {  // create player object
                player = Player(row, col, c);
            }
            else if (c == 'R') {  // add robots to robots vector
                Robot rb = Robot(row, col, count+1);
                robots.push_back(rb);
            }
            else if (c == 'O') {  // add exit doors to doors vector
                Door dr = { c, row, col };
                doors.push_back(dr);
            }
        }
    }

    //cout << robots.at().getPosition().col << endl;

}

bool Game::play() {
    cout << maze.getnumRows() << ' ' << maze.getnumCols();
    return true;
}
