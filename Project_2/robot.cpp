#include "structs.h"
#include "robot.h"

using namespace std;

int Robot::robotCounter = 1;

Robot::Robot() {
	robotCounter = 1;
}

Robot::Robot(int row, int col, char symbol) {
	this->row = row;
	this->col = col;
	this->id = robotCounter;
	this->symbol = symbol;
	alive = true;
	robotCounter++;
}

int Robot::getID() const {
	return id;
}

char Robot::getSymbol() const
{
	return symbol;
}

int Robot::getRow() const {
	return row;
}

int Robot::getCol() const {
	return col;
}

Position Robot::getPosition() const {
	return { row, col };
}

bool Robot::isAlive() const {
	return alive;
}

void Robot::setAsDead() {
    alive = false;
    symbol = 'r';
}

void Robot::move(Movement delta) {
    row += delta.dRow;
    col += delta.dCol;
}

void Robot::move(const Position& position) {
    row = position.row;
    col = position.col;
}

Movement Robot::minimumPath(Position &pl) const {
    if (col > pl.col) {
        if (row > pl.row)
            return { -1, -1 };
        if (row < pl.row)
            return { 1, -1 };
        if (row == pl.row)
            return { 0, -1 };
    }
    else if (col < pl.col) {
        if (row > pl.row)
            return { -1, 1 };
        if (row < pl.row)
            return { 1, 1 };
        if (row == pl.row)
            return { 0, 1 };
    }
    else if (col == pl.col) {
        if (row > pl.row)
            return { -1, 0 };
        if (row < pl.row)
            return { 1, 0 };
    }
}
