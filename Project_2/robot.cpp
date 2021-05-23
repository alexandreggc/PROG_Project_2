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
