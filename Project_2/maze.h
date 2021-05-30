#ifndef MAZE_H
#define MAZE_H
#include "door.h"
#include "post.h"

#include <vector>

class Maze {
	public:
		Maze();
		Maze(int numRows, int numCols);
		void addPost(const Post& post);
		void addDoor(const Door& door);
		void remove(const Post& post);
		void remove(const Door& door);
		void changePost(const Post& post);
		int getnumRows() const;
		int getnumCols() const;
		std::vector<Post> getPosts();
		std::vector<Door> getDoors();
	private:
		int numRows, numCols;
		std::vector<Post> posts;
		std::vector<Door> doors;
};

#endif