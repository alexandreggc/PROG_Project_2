#pragma once
#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <vector>
#include <string>

#include "structs.h"
#include "robot.h"
#include "player.h"
#include "maze.h"

using namespace std;

class Game {
	public:
		enum Status { WON, LOST, RUNNING};
		static int gameStatus;
		Game(const string& filename);
		// This constructor should initialize the Maze, the vector of Robots, and the Player,
		// using the chars read from the file
		bool play(); // implements the game loop; returns true if player wins, false otherwise
	private:
		void showGameDisplay() const;
		void updateGameDisplay();
		void buildDisplay();
		void clearDisplay();
		bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
		bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
		bool validMove(Movement& move);
		void updatePlayer(Movement& move);
		bool samePosition(const Position& p1, const Position& p2) const;
		// other methods, for example:
		// to check if player is trying to move to a valid place
		// to apply a valid play and check collisions
		// to check if two robots collide (and possibly set them as dead)
		// etc.
	private:
		fstream file;
		vector<vector<char>> gameDisplay;
		Maze maze;
		Player player;
		vector<Robot> robots;
		//other attributes
};

#endif