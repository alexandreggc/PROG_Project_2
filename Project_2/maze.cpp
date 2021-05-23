#include "maze.h"

Maze::Maze() {}

Maze::Maze(int numRows, int numCols) {
	this->numRows = numRows;
	this->numCols = numCols;
}

void Maze::addPost(const Post& post){ //, const Position& position) { 
	posts.push_back(post);
}

void Maze::addDoor(const Door& door) {
	doors.push_back(door);
}

void Maze::remove(const Post& postA) {
	int index = 0;
	for (Post& postA : posts) {
		if (postA.getID() == postA.getID())
			posts.erase(posts.begin() + index);
		index++;
	}
}

void Maze::remove(const Door& doorA) {
	int index = 0;
	for (Door& doorB : doors) {
		if (doorA.getID() == doorB.getID())
			doors.erase(doors.begin() + index);
		index++;
	}
}

int Maze::getnumCols() const {
	return numCols;
}

vector<Post> Maze::getPosts() const {
	return posts;
}

vector<Door> Maze::getDoors() const {
	return doors;
}

int Maze::getnumRows() const {
	return numRows;
}