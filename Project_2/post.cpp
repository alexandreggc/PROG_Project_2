#include "structs.h"
#include "post.h"

Post::Post(int row, int col, char type) {
	this->row = row;
	this->col = col;
	this->type = type;
}

int Post::getRow() const {
	return row;
}

int Post::getCol() const {
	return col;
}

Position Post::getPosition() const {
	return {row, col};
}

char Post::getSymbol() const {
	return type;
}

bool Post::isElectrified() const {
	if (type == '*')
		return true;
	return false;
}
