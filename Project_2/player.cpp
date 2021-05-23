#include "structs.h"
#include "player.h"
#include <iostream>

using namespace std;

Player::Player() {}

Player::Player(int row, int col, char symbol) {
	this->row = row;
	this->col = col;
	this->symbol = 'H';
	this->alive = true;
}

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

Movement Player::moveDirection(char dir) const{
    if (dir == 'Q') return { -1, -1 };
    if (dir == 'W') return { -1, 0 };
    if (dir == 'E') return { -1, 1 };
    if (dir == 'A') return { 0, -1 };
    if (dir == 'S') return { 0, 0 };
    if (dir == 'D') return { 0, 1 };
    if (dir == 'Z') return { 1, -1 };
    if (dir == 'X') return { 1, 0 };
    if (dir == 'C') return { 1, 1 };
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
