//T07_G09
#include "structs.h"
#include "post.h"

#include <iostream>

int Post::postCounter = 1;

Post::Post() {
	postCounter = 1; // reset post counter
	row = NULL;
	col = NULL;
	type = NULL;
	id = NULL;
}

Post::Post(int row, int col, char type) {
	this->row = row;
	this->col = col;
	this->type = type;
	id = postCounter;
	postCounter++;
}

int Post::getRow() const {
	return row;
}

int Post::getCol() const {
	return col;
}

int Post::getID() const {
	return id;
}

Position Post::getPosition() const {
	return {row, col};
}

char Post::getSymbol() const { // get char representation of Post
	return type;
}

bool Post::isElectrified() const {
	if (type == '*')
		return true;
	return false;
}

void Post::setNoElectric() {
	type = '+';
}
