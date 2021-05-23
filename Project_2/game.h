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
		enum State { LOST, WON, RUNNING};
		static int gameState;
		Game(const string& filename);
		// This constructor should initialize the Maze, the vector of Robots, and the Player,
		// using the chars read from the file
		bool play(); // implements the game loop; returns true if player wins, false otherwise
	private:
		void showGameDisplay() const;
		void updateGameDisplay();
		void buildDisplay();
		void clearDisplay();
		void displayMaze();
		bool collide(const Position& pos, const Post& post);
		bool collide(const Position& pos, const Player& player);
		bool collide(const Position& pos, const Robot& robot);
		bool collide(const Position& pos, const Door& door);
		bool validMove(Movement& delta);
		void updatePlayer(Movement& delta);
		void updateRobot(Robot &robot, Movement& delta);
		void robotsAlive() const;
		void remove(Robot& robot);
		bool gameOver() const;
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