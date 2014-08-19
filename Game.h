#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Level.h"
#include "Parser.h"

class Game {
public:

	void init();

	Level * current_level;
	bool nextLevel();

	bool isPaused();
	void pause();
	void resume();

private:

	std::vector<Level> _levels;
};

#endif