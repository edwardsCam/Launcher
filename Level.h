#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Planet.h"
#include "Player.h"

struct PlanetInfo {
	Planet p;
	unsigned int xpos;
	unsigned int ypos;
};

enum gamestate {
	INTRO = 0,
	PAUSED = 1,
	INITIAL_READY = 10,
	DRAGGING  = INITIAL_READY + 1,
	LAUNCHING = INITIAL_READY + 2,
	IN_PLAY   = INITIAL_READY + 3,
};

class Level {
public:

	int id;
	Player _player;
	bool active;
	gamestate _state;

	sf::Vector2u getPlayerPos();

	void drawPlanets(sf::RenderWindow window);

private:

	std::vector<PlanetInfo> _planets;

};

#endif