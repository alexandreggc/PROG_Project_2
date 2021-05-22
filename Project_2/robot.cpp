#include "structs.h"
#include "robot.h"

using namespace std;

Robot::Robot(int row, int col, int id, char symbol) {
	this->row = row;
	this->col = col;
	this->id = id;
	this->symbol = symbol;
	alive = true;
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
