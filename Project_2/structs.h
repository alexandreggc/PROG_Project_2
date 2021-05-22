#pragma once

struct Position
{
	int row, col;
};

struct Movement
{
	int dRow, dCol;
};

struct Door {
	char chr;
	int row, col;
};