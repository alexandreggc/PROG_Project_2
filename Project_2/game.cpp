#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

int Game::gameStatus = RUNNING;

Game::Game(const string& filename) {
    Robot rb; // reset robot counter 
    Door dr;  // reset door counter
    Post p;   // reset post counter

    file.open(filename);
    int rows, cols;
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
                Robot rb = Robot(row, col, c);
                robots.push_back(rb);
            }
            else if (c == 'O') {  // add exit doors to doors vector
                Door dr = Door(row, col, c);
                maze.addDoor(dr);
            }
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

}

bool Game::play() {
    gameStatus = RUNNING;
    cout << maze.getnumRows() << ' ' << maze.getnumCols();
    buildDisplay();
    while (true) {
        clearDisplay();
        updateGameDisplay();
        showGameDisplay();
        Movement move = player.input();
        if (validMove(move)) {
            updatePlayer(move);
            if (gameStatus == WON)
                return true;
            else if (gameStatus == LOST)
                return false;
        }
        else {
            cout << "Invalid movement." << endl;
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
    for (const Door &door : maze.getDoors()) { // place doors in maze
        gameDisplay.at(door.getRow()).at(door.getCol()) = door.getSymbol();
    }
}

void Game::buildDisplay() {
    char empty = ' ';
    vector<char> line(maze.getnumCols(), ' ');
    for (int row = 0; row < maze.getnumRows(); row++) {
        gameDisplay.push_back(line);
    }
}

void Game::clearDisplay() {
    for (vector<char> &ln : gameDisplay)
        for (size_t i = 0; i < ln.size(); i++) {
            ln.at(i) = ' ';
        }
}

bool Game::collide(Robot& robot, Post& post) {
    if (robot.getCol() == post.getCol() && robot.getRow() == post.getRow())
        return true;
    return false;
}

bool Game::collide(Robot& robot, Player& player) {
    if (robot.getCol() == player.getCol() && robot.getRow() == player.getRow())
        return true;
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

void Game::updatePlayer(Movement& move) {
    Position newPos = { player.getRow() + move.dRow, player.getCol() + move.dCol };
    for (const Post& post : maze.getPosts()) {  // check if the player collided with a post
        if (post.isElectrified() && samePosition(newPos, post.getPosition())) {
            player.setAsDead();
            gameStatus = LOST;
            return;
        }
    }
    for (const Robot& robot : robots) {  // check if the player collided with a robot
        if (robot.isAlive() && samePosition(newPos, robot.getPosition())) {
            player.move(move);
            player.setAsDead();
            gameStatus = LOST;
            return;
        }
    }
    for (const Door& door : maze.getDoors()) {  // check if the player entered a door
        if (samePosition(newPos, door.getPosition())) {
            maze.remove(door); // erase the exit door use by the player
            player.move(move);
            gameStatus = WON;
            return;
        }
    }
    player.move(move);
    gameStatus = RUNNING;
    return;
}

bool Game::samePosition(const Position& p1, const Position& p2) const {
    if (p1.col == p2.col && p1.row == p2.row)
        return true;
    return false;
}

