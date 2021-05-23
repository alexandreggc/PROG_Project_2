#pragma once
#ifndef POST_H
#define POST_H
#include "structs.h"

class Post {
	public:
		Post();
		Post(int row, int col, char type);
		int getRow() const;
		int getCol() const;
		int getID() const;
		Position getPosition() const;
		char getSymbol() const; // get char representation of Post
		bool isElectrified() const;
		//other methods
	private:
		static int postCounter;
		int row, col;
		int id;
		char type; // '*' - electrified; '+'- non-electrified
		// other attributes (?)
		// could also have a state, like the robot(?)
};

#endif