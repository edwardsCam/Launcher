#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Planet.h"
#include "Player.h"

struct PlanetInfo {
	Planet p;
	sf::Vector2u pos;
};

enum gamestate {
	INTRO = 0,
	PAUSED = 1,
	INITIAL_READY = 10,
	DRAGGING  = INITIAL_READY + 1,
	LAUNCHING = INITIAL_READY + 2,
	IN_PLAY   = INITIAL_READY + 3,
};

class Game {
public:

	Player _player;
	bool isPaused();
	void pause();
	void resume();

	sf::Vector2u getPlayerPos();

private:

	std::vector<PlanetInfo> _planets;
	gamestate _state;
};

#endif