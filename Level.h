#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Planet.h"
#include "Player.h"
#include "Goal.h"

enum gamestate {
	PAUSED = 0,
	INITIAL_READY = 10,
	DRAGGING  = INITIAL_READY + 1,
	LAUNCHING = INITIAL_READY + 2,
	IN_PLAY   = INITIAL_READY + 3,
	CRASHED   = INITIAL_READY + 4,
	WON       = INITIAL_READY + 5
};

class Level {
public:

	Level();

	unsigned int id;
	bool active, released;
	Player _dot;
	Goal goal;
	gamestate _state, _pstate;
	unsigned int nPlanets;
	int x_i, y_i, x_r, y_r;
	std::vector<sf::Vertex> stream, pstream;

	sf::Vector2f getGravitationalPull();
	Planet * planetAt(int i);

	sf::CircleShape drawPlanet(unsigned int i);
	sf::CircleShape drawPlayer();

	bool isCrashed();
	void setPlayerPos(sf::Vector2i pos);
	void setPlayerPos(int x, int y);
	void addPlanet(Planet p);

	void reset();
private:
	std::vector<Planet> _planets;
};

#endif