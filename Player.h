#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"

class Player {
public:
	Player();
	sf::Vector2u pos;
	sf::Vector2u velocity;
	unsigned int speed;

private:



};

#endif