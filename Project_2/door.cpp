//T07_G09
#include "door.h"
#include <iostream>

int Door::doorCounter = 1;

Door::Door() {
	doorCounter = 1; // reset door counter
	row = NULL;
	col = NULL;
	chr = NULL;
	id = NULL;
}

Door::Door(int row, int col, char chr) {
	this->row = row;
	this->col = col;
	this->chr = chr;
	id = doorCounter;
	doorCounter++;
}

int Door::getRow() const {
	return row;
}

int Door::getCol() const {
	return col;
}

int Door::getID() const {
	return id;
}

Position Door::getPosition() const {
	return {row, col};
}

char Door::getSymbol() const {
	return chr;
}
