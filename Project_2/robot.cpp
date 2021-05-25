#include "structs.h"
#include "robot.h"
#include <iostream>

using namespace std;

int Robot::robotCounter = 1;

Robot::Robot() {
	robotCounter = 1; // reset robot counter
    row = NULL;
    col = NULL;
    id = NULL;
    symbol = NULL;
    alive = NULL;
}

Robot::Robot(int row, int col, char symbol) {
	this->row = row;
	this->col = col;
	this->symbol = symbol;
	alive = true;
    id = robotCounter;
    robotCounter++;
}

int Robot::getID() const {
	return id;
}

char Robot::getSymbol() const { // get char representation of robot (R if alive, r if dead)
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
    return { NULL, NULL };
}
