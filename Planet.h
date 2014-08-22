#ifndef PLANET_H
#define PLANET_H

#include "SFML\Graphics.hpp"

class Planet {
public:
	float radius;
	unsigned int xpos;
	unsigned int ypos;
	sf::Vector2f getPull(const sf::Vector2i);
};

#endif