#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

int Game::gameState = RUNNING;

Game::Game(const string& filename) {
    Robot rb; // reset robot counter 
    Door dr;  // reset door counter
    Post p;   // reset post counter

    file.open(filename);
    int rows, cols;
    char c;
    file >> rows >> c >> cols;  // get number of rows and columns of the maze
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the first line
    maze = Maze(rows, cols);

    // search for all the maze elements and create new objects for them
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

// gameloop functions that return true if player won otherwise return false 
bool Game::play() {
    gameState = RUNNING;
    buildDisplay();
    while (true) {
        displayMaze();
        // update player position and checks if game is over
        while (true) {
            Movement delta = player.input();
            if (validMove(delta)) {
                updatePlayer(delta);
                if (gameOver()) {
                    displayMaze();
                    return gameState;
                }
                break;
            }
            else {
                cout << "Invalid movement." << endl;
            }
        }

        // update each robot position and checks if game is over
        for (Robot &robot : robots) {
            if (robot.isAlive()) {
                Position playerPos = player.getPosition();
                Movement delta = robot.minimumPath(playerPos);
                updateRobot(robot, delta);
                if (gameOver()) {
                    displayMaze();
                    return gameState;
                }
            }
        }
    }
    return true;
}

// display the maze elements in console
void Game::showGameDisplay() const {
    for (vector<char> vct : gameDisplay) {
        cout << endl;
        for (char chr : vct) {
            cout << chr;
        }
    }
    cout << endl;
}

// update the game display vector with all maze characthers
void Game::updateGameDisplay(){
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

// build an empty game display vector
void Game::buildDisplay() {
    char empty = ' ';
    vector<char> line(maze.getnumCols(), ' ');
    for (int row = 0; row < maze.getnumRows(); row++) {
        gameDisplay.push_back(line);
    }
}

// clear all objects from game display vector
void Game::clearDisplay() {
    for (vector<char> &ln : gameDisplay)
        for (size_t i = 0; i < ln.size(); i++) {
            ln.at(i) = ' ';
        }
}

// display updated maze in console
void Game::displayMaze() {
    clearDisplay();
    updateGameDisplay();
    showGameDisplay();
}

// check collision between a specified position and a post
bool Game::collide(const Position& pos, const Post& post) {
    if (pos.col == post.getPosition().col && pos.row == post.getPosition().row)
        return true;
    return false;
}

// check collision between a specified position and the player
bool Game::collide(const Position& pos, const Player& player) {
    if (pos.col == player.getPosition().col && pos.row == player.getPosition().row)
        return true;
    return false;
}

// check collision between a specified position and a robot
bool Game::collide(const Position& pos, const Robot& robot) {
    if (pos.col == robot.getPosition().col && pos.row == robot.getPosition().row)
        return true;
    return false;
}

// check collision between a specified position and a door
bool Game::collide(const Position& pos, const Door& door) {
    if (pos.col == door.getPosition().col && pos.row == door.getPosition().row)
        return true;
    return false;
}

// check if delta movement is a valid player movement
bool Game::validMove(Movement& delta) { 
    Position newPos = { player.getRow() + delta.dRow, player.getCol() + delta.dCol };
    cout << newPos.row << " " << newPos.col << endl;
    for (const Post& post : maze.getPosts()) {
        if (!post.isElectrified() && collide(newPos, post))
            return false;
    }
    for (const Robot& robot : robots) {
        if (!robot.isAlive() && collide(newPos, robot))
            return false;
    }
    return true;
}

// update player position and checks his collisions
void Game::updatePlayer(Movement& delta) { 
    Position newPlayerPos = { player.getRow() + delta.dRow, player.getCol() + delta.dCol };
    for (const Post& post : maze.getPosts()) {  // check if the player collided with a post
        if (post.isElectrified() && collide(newPlayerPos, post)) {
            player.setAsDead();
            gameState = LOST;
            return;
        }
    }
    for (const Robot& robot : robots) {  // check if the player collided with a robot
        if (robot.isAlive() && collide(newPlayerPos, robot)) {
            player.move(newPlayerPos);
            player.setAsDead();
            gameState = LOST;
            return;
        }
    }
    for (const Door& door : maze.getDoors()) {  // check if the player entered a door
        if (collide(newPlayerPos, door)) {
            maze.remove(door); // erase the exit door use by the player
            player.move(newPlayerPos);
            gameState = WON;
            return;
        }
    }
    // if player didn't collide with anything then move
    player.move(newPlayerPos);
    gameState = RUNNING;
    return;
}

// update robot position and checks his collisions
void Game::updateRobot(Robot &robot,  Movement& delta) { 
    Position newRobotPos = { robot.getRow() + delta.dRow, robot.getCol() + delta.dCol };
    for (Post& post : maze.getPosts()) {  // check if the robot collided with a post
        if (collide(newRobotPos, post)) {
            if (post.isElectrified()) {
                maze.changePost(post);
            }
            else {
                maze.remove(post);
                robot.move(newRobotPos);
            }
            robot.setAsDead();
            robotsAlive();
            return;
        }
    }
    for (Robot& rb : robots) {  // check if the robot collided with another robot
        if (collide(newRobotPos, rb)) {
            if (rb.isAlive()) rb.setAsDead();
            robot.move(newRobotPos);
            robot.setAsDead();
            robotsAlive();
            return;
        }
    }
    if (collide(newRobotPos, player)) { // check if the robot collided with player
        player.setAsDead();
        gameState = LOST;
        return;
    }
    // if robot didn't collide with anything then move
    robot.move(newRobotPos);
    gameState = RUNNING;
    return;
}

// check if there are any robots alive if not then player won
void Game::robotsAlive() const {
    for (const Robot& robot : robots) {
        if (robot.isAlive()) {
            gameState = RUNNING;
            return;
        }
    }
    gameState = WON;
    return;
}

// returns true if the game ended if not returns false and the game continues
bool Game::gameOver() const {
    if (gameState == WON || gameState == LOST)
        return true;
    else if (gameState == RUNNING)
        return false;
    return false;
}
