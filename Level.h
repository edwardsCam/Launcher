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
	Player _player;
	bool active;
	gamestate _state;

	sf::Vector2u getPlayerPos();

	void drawPlanets(sf::RenderWindow window);

	void addPlanet(Planet p);
	void setPlayerPos(sf::Vector2u pos);
	void setPlayerPos(unsigned int x, unsigned int y);

private:

	std::vector<Planet> _planets;

};

#endif