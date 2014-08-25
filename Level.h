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
	int start_angle;

	bool released;

	sf::CircleShape drawPlanet(unsigned int i);
	sf::CircleShape drawPlayer();
	void movePlayer(int x, int y);

	void addPlanet(Planet p);
	void setPlayerPos(sf::Vector2i pos);
	void setPlayerPos(int x, int y);

	Planet * planetAt(int i);
	sf::Vector2f getGravitationalPull();

private:
	std::vector<Planet> _planets;
};

#endif