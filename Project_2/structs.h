#pragma once

#include <string>

struct Position
{
	int row, col;
};

struct Movement
{
	int dRow, dCol;
};

struct NameAndTime {
    std::string name;
    int time;
};
