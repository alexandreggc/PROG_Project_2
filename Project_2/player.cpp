#include "player.h"

Player::Player() {}

Player::Player(int row, int col, char symbol) {
	this->row = row;
	this->col = col;
	this->symbol = 'H';
	this->alive = true;
}