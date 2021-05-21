#pragma once
#ifndef MAZE_H
#define MAZE_H
#include "post.h"
#include "robot.h"

class Maze {
	public:
		Maze();
		Maze(int numRows, int numCols);
		bool addPost(const Post &post, const Position &position);
		int getnumRows() const;
		int getnumCols() const;
		// other methods
	private:
		int numRows, numCols;
		// data structure that represents the posts
};

#endif