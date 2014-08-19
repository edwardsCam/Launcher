#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Planet.h"
#include "Player.h"

class Game {
public:

	Player _player;
	bool isPaused();
	void pause();
	void resume();

	sf::Vector2u getPlayerPos();

private:

	std::vector<Planet> planets;

};

#endif