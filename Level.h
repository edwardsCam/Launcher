#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Planet.h"
#include "Player.h"

enum gamestate {
	PAUSED = 0,
	INITIAL_READY = 10,
	DRAGGING  = INITIAL_READY + 1,
	LAUNCHING = INITIAL_READY + 2,
	IN_PLAY   = INITIAL_READY + 3,
	CRASHED   = INITIAL_READY + 4
};

class Level {
public:
	Level();
	int id;
	bool active;
	gamestate _state;
	gamestate _prevstate;
	Player _player;

	unsigned int numPlanets;
	int initx, inity, releasex, releasey;

	bool released;

	std::vector<sf::Vertex> stream;

	sf::CircleShape drawPlanet(unsigned int i);
	sf::CircleShape drawPlayer();
	void movePlayer(int x, int y);

	void reset();

	void addPlanet(Planet p);
	void setPlayerPos(sf::Vector2i pos);
	void setPlayerPos(int x, int y);

	bool isCrashed();

	Planet * planetAt(int i);
	sf::Vector2f getGravitationalPull();

private:
	std::vector<Planet> _planets;
};

#endif