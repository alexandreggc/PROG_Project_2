#pragma once
#ifndef GAME_H
#define GAME_H
#include "structs.h"
#include "robot.h"
#include "player.h"
#include "maze.h"

#include <fstream>
#include <vector>
#include <string>

class Game {
	public:
		enum State { LOST, WON, RUNNING};
		static int gameState;
		Game(const std::string& filename);
		bool play();
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
		bool gameOver() const;
	private:
		std::fstream file;
		std::vector<std::vector<char>> gameDisplay;
		Maze maze;
		Player player;
		std::vector<Robot> robots;
};

#endif