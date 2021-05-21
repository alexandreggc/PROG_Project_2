#include "robot.h"

using namespace std;

Robot::Robot(int row, int col, int id) {
	this->row = row;
	this->col = col;
	this->id = id;
	alive = true;
}

Position Robot::getPosition() const {
	return { row, col };
}