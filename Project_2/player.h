#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "structs.h"

#include <vector>
#include <map>

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
		void move(Position position);
		void setKeys();

	private:
		std::map<char, Movement> keys;
		Movement moveDirection(char dir);
		int row, col;
		bool alive;
		char symbol;
};

#endif
