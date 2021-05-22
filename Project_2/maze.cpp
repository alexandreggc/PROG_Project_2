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

vector<Post> Maze::getPosts() const {
	return posts;
}

int Maze::getnumRows() const {
	return numRows;
}