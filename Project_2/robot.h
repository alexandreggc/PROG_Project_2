#ifndef ROBOT_H
#define ROBOT_H
#include "structs.h"

class Robot {
	public:
		Robot();
		Robot(int row, int col, char symbol);
		int getID() const;
		char getSymbol() const; 
		int getRow() const;
		int getCol() const;
		Position getPosition() const;
		bool isAlive() const;
		void setAsDead();
		void move(const Position& position);
		Movement minimumPath(Position &pl) const;
	private:
		static int robotCounter; //used to attribute automatically the id to the robots
		int id, row, col;
		bool alive;
		char symbol;
};

#endif