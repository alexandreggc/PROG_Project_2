#pragma once
#ifndef MAZE_H
#define MAZE_H
#include "post.h"
#include "robot.h"
#include <vector>

using namespace std;

class Maze {
	public:
		Maze();
		Maze(int numRows, int numCols);
		void addPost(const Post& post); //, const Position &position);
		int getnumRows() const;
		int getnumCols() const;
		vector<Post> getPosts() const;
		// other methods
	private:
		int numRows, numCols;
		vector<Post> posts;
};

#endif