#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

Game::Game(const string& filename) {
    file.open(filename);
    int rows, cols, count=0;
    char c;
    file >> rows >> c >> cols;  // get number of rows and columns of the maze
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    maze = Maze(rows, cols);

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
                Robot rb = Robot(row, col, count+1, c);
                robots.push_back(rb);
            }
            else if (c == 'O') {  // add exit doors to doors vector
                Door dr = { c, row, col };
                doors.push_back(dr);
            }
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

}

bool Game::play() {
    cout << maze.getnumRows() << ' ' << maze.getnumCols();
    buildDisplay();

    while (true) {
        updateGameDisplay();
        showGameDisplay();
        Movement move = player.input();
        if (validMove(move)) {
            cout << "valid move" << endl;
        }
        else {
            cout << "invalid move" << endl;
        }
    }
    return true;
}

void Game::showGameDisplay() const {
    for (vector<char> vct : gameDisplay) {
        cout << endl;
        for (char chr : vct) {
            cout << chr;
        }
    }
    cout << endl;
}

void Game::updateGameDisplay() {
    // place player in maze
    gameDisplay.at(player.getRow()).at(player.getCol()) = player.getSymbol();

    for (const Post &post : maze.getPosts()) { // place posts in maze
        gameDisplay.at(post.getRow()).at(post.getCol()) = post.getSymbol();
    }
    for (const Robot &robot : robots) { // place robots in maze
        gameDisplay.at(robot.getRow()).at(robot.getCol()) = robot.getSymbol();
    }
    for (const Door &door : doors) { // place doors in maze
        gameDisplay.at(door.row).at(door.col) = door.chr;
    }
}

void Game::buildDisplay() {
    char empty = ' ';
    vector<char> line(maze.getnumCols(), ' ');
    for (int row = 0; row < maze.getnumRows(); row++) {
        gameDisplay.push_back(line);
    }
}

bool Game::collide(Robot& robot, Post& post)
{
    return false;
}

bool Game::collide(Robot& robot, Player& player)
{
    return false;
}

bool Game::validMove(Movement& move) {
    Position newPos = { player.getRow() + move.dRow, player.getCol() + move.dCol };
    cout << newPos.row << " " << newPos.col << endl;
    for(const Post& post : maze.getPosts()) {
        if (!post.isElectrified() && samePosition(newPos, post.getPosition()))
            return false;
    }
    for (const Robot& robot : robots) { 
        if (!robot.isAlive() && samePosition(newPos, robot.getPosition()))
            return false;
    }
    return true;
}

bool Game::samePosition(const Position& p1, const Position& p2) const {
    if (p1.col == p2.col && p1.row == p2.row)
        return true;
    return false;
}
