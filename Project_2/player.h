#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "structs.h"

class Player {
	public:
		Player();
		Player(int row, int col, char symbol);
		Movement input();
		Position getPosition() const;
		int getRow() const;
		int getCol() const;
		char getSymbol() const;
		bool isAlive() const;
		void setAsDead();
		void move(Movement delta);

	private:
		Movement moveDirection(char dir) const;
		int row, col;
		bool alive;
		char symbol;
};

#endif
