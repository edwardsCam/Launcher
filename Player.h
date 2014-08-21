#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"

class Player {
public:
	Player();
	sf::Vector2i pos;
	sf::Vector2i velocity;
	unsigned int speed;
};

#endif