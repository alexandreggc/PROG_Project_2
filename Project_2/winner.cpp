#include "leaderboard.h"
#include "structs.h"

#include <iostream>
#include <string>

using namespace std;

Winner::Winner(string name, double time){
    this->name = name;
    this->time = time;
}

string Winner::getName() {
    return name;
}

double Winner::getTime() {
    return time;
}

void Winner::setName(string name) {
    this->name = name;
}

void Winner::setTime(double time) {
    this->time = time;
}
