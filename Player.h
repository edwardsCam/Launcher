#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"

#define playersize 15

class Player {
public:
	Player();
	sf::Vector2i p;
	sf::Vector2f v, a;
	float speed_bufferx, speed_buffery;
};

#endif