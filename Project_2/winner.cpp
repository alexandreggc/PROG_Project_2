//T07_G09
#include "leaderboard.h"
#include "structs.h"

#include <iostream>
#include <string>

using namespace std;

Winner::Winner(string name, int time){
    this->name = name;
    this->time = time;
}

string Winner::getName() {
    return name;
}

int Winner::getTime() {
    return time;
}

void Winner::setTime(int time) {
    this->time = time;
}

// operator to compare two winners used by sort function from algorithm library
bool Winner::operator<(const Winner& w) {
	if (this->time < w.time)
		return true;
	else if (this->time > w.time)
		return false;
	else
		if (this->name < w.name)
			return true;
		else
			return false;
}
