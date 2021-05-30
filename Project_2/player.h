//T07_G09
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
	private:
		void setKeys();
		Movement moveDirection(char dir);
	private:
		std::map<char, Movement> keys;
		int row, col;
		bool alive;
		char symbol;
};

#endif
