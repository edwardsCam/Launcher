#include "Planet.h"

#define distance_damp 0.09
#define min 0.05
#define max 10

sf::Vector2f Planet::getPull(const sf::Vector2u loc) {

	double distx = (double)xpos - loc.x;
	double disty = (double)ypos - loc.y;

	float distance = sqrt(distx * distx + disty * disty);
	distance *= distance_damp;
	distance *= distance;

	float pull = radius / distance;
	if (pull < min)
		pull = min;
	else if (pull > max)
		pull = max;

	sf::Vector2f ret(pull * (distx/(abs(distx)+abs(disty))), pull * (disty/(abs(distx)+abs(disty))));
	return ret;
}