#include "game.h"
#include <fstream>
using namespace std;

Game::Game(const string& filename) {
    file.open(filename);
}

bool Game::play() {
    return true;
}

bool Game::isValid() {
    if (file.is_open() && file.good()) 
        return true;
    else
        return false;
}
