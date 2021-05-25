#pragma once
#ifndef DOOR_H
#define DOOR_H
#include "structs.h"

class Door {
	public:
		Door();
		Door(int row, int col, char chr);
		int getRow() const;
		int getCol() const;
		int getID() const;
		int getNum() const;
		Position getPosition() const;
		char getSymbol() const;
	private:
		static int doorCounter; //used to attribute automatically the id to the doors
		int row, col;
		int id;
		char chr;
};

#endif