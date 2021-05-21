#include "maze.h"

Maze::Maze() {}

Maze::Maze(int numRows, int numCols) {
	this->numRows = numRows;
	this->numCols = numCols;
}

void Maze::addPost(const Post& post){ //, const Position& position) { 
	posts.push_back(post);
}

int Maze::getnumCols() const {
	return numCols;
}

int Maze::getnumRows() const {
	return numRows;
}