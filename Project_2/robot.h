#pragma once
#ifndef ROBOT_H
#define ROBOT_H
#include "structs.h"

class Robot {
	public:
		static int robotCounter; //used to attribute automatically the id to the robots
		Robot();
		Robot(int row, int col, char symbol);
		int getID() const;
		char getSymbol() const; // get char representation of robot (R if alive, r if dead)
		int getRow() const;
		int getCol() const;
		Position getPosition() const;
		bool isAlive() const;
		void setAsDead();
		void move(const Position& position);
		Movement minimumPath(Position &pl) const;
	private:
		int id;
		int row, col;
		bool alive;
		char symbol;
};

#endif