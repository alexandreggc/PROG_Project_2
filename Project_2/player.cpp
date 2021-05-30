#include "structs.h"
#include "player.h"

#include <iostream>
#include <limits>

using namespace std;

Player::Player() {
    row = NULL;
    col = NULL;
    symbol = NULL;
    alive = NULL;
}

Player::Player(int row, int col, char symbol) {
    this->row = row;
	this->col = col;
	this->symbol = 'H';
	this->alive = true;
    setKeys();
}

// get player keyboard input
Movement Player::input() {
    char dir;
    cout << endl;
    cout << "Enter the position you want to move to: ";
    while (true) {
        cin >> dir;
        dir = toupper(dir);
        if (cin.peek() == '\n' && !cin.fail() && (dir == 'Q' || dir == 'W' || dir == 'A' ||
            dir == 'S' || dir == 'Z' || dir == 'D' || dir == 'X' || dir == 'C' || dir == 'E'))
        {
            return moveDirection(dir);
        }
        else if (cin.fail() && cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Please enter a valid position: ";
    }
}

Position Player::getPosition() const{
    return {row, col};
}

Movement Player::moveDirection(char key){
    return keys[key];
}

int Player::getRow() const {
	return row;
}

int Player::getCol() const {
	return col;
}

char Player::getSymbol() const {
	return symbol;
}

bool Player::isAlive() const {
    return alive;
}

void Player::setAsDead() {
    alive = false;
    symbol = 'h';
}

void Player::move(Position position) {
    row = position.row;
    col = position.col;
}

// establish the keys to the corresponding movement vectors
void Player::setKeys() {
    keys['Q'] = { -1,-1 };
    keys['W'] = { -1, 0 };
    keys['E'] = { -1, 1 };
    keys['A'] = { 0, -1 };
    keys['S'] = { 0, 0 };
    keys['D'] = { 0, 1 };
    keys['Z'] = { 1, -1 };
    keys['X'] = { 1, 0 };
    keys['C'] = { 1, 1 };
}
