#include "door.h"
using namespace std;

int Door::doorCounter = 1;

Door::Door() {
	doorCounter = 1;
}

Door::Door(int row, int col, char chr) {
	this->row = row;
	this->col = col;
	this->chr = chr;
	this->id = doorCounter;
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

int Door::getNum() const
{
	return doorCounter;
}

Position Door::getPosition() const {
	return {row, col};
}

char Door::getSymbol() const {
	return chr;
}
