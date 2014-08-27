#include "Planet.h"

#define distance_damp 0.03
#define min 0.05
#define max 20

sf::Vector2f Planet::getPull(const sf::Vector2i loc) {

	double distx = (double)xpos - loc.x;
	double disty = (double)ypos - loc.y;

	double distance = sqrt(distx * distx + disty * disty);
	distance *= distance_damp;
	distance *= distance;

	double pull = radius / distance;
	if (pull < min)
		pull = min;
	else if (pull > max)
		pull = max;

	return sf::Vector2f(pull * (distx/(abs(distx)+abs(disty))), pull * (disty/(abs(distx)+abs(disty))));
}