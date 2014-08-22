#include "Planet.h"

#define pull 8

sf::Vector2f Planet::getPull(const sf::Vector2i loc) {

	sf::Vector2f ret;
	//todo
	int distx, disty;
	distx = xpos - loc.x;
	disty = ypos - loc.y;

	ret.x = (1.0)/((double)distx/pull);
	ret.y = (1.0)/((double)disty/pull);

	return ret;
}