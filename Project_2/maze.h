#pragma once
#ifndef MAZE_H
#define MAZE_H
#include "door.h"
#include "post.h"
#include "robot.h"
#include <vector>

using namespace std;

class Maze {
	public:
		Maze();
		Maze(int numRows, int numCols);
		void addPost(const Post& post); //, const Position &position);
		void addDoor(const Door& door);
		void remove(const Post& post);
		void remove(const Door& door);
		int getnumRows() const;
		int getnumCols() const;
		vector<Post> getPosts() const;
		vector<Door> getDoors() const;
		// other methods
	private:
		int numRows, numCols;
		vector<Post> posts;
		vector<Door> doors;
};

#endif