#include "maze.h"

Maze::Maze() {
	numCols = NULL;
	numRows = NULL;
}

Maze::Maze(int numRows, int numCols) {
	this->numRows = numRows;
	this->numCols = numCols;
}

void Maze::addPost(const Post& post){
	posts.push_back(post);
}

void Maze::addDoor(const Door& door) {
	doors.push_back(door);
}

// remove post from posts vector
void Maze::remove(const Post& postA) {
	int index = 0;
	for (Post& postB : posts) {
		if (postB.getID() == postA.getID())
			posts.erase(posts.begin() + index);
		index++;
	}
}

// remove door from doors vector
void Maze::remove(const Door& doorA) {
	int index = 0;
	for (Door& doorB : doors) {
		if (doorA.getID() == doorB.getID())
			doors.erase(doors.begin() + index);
		index++;
	}
}

// change a post from electrified to non_electrified
void Maze::changePost(const Post& postA) {
	for (Post& postB : posts) {
		if (postB.getID() == postA.getID())
			postB.setNoElectric();
	}
}

int Maze::getnumCols() const {
	return numCols;
}

std::vector<Post> Maze::getPosts() {
	return posts;
}

std::vector<Door> Maze::getDoors() {
	return doors;
}

int Maze::getnumRows() const {
	return numRows;
}