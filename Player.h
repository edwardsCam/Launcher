#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"

class Player {
public:
	Player();
	sf::Vector2u p;
	sf::Vector2f v, a;
	float speed_bufferx, speed_buffery;
};

#endif