#ifndef GOAL_H
#define GOAL_H

#include "SFML\Graphics.hpp"
#include "Player.h"

#define goal_size 20

class Goal {

public:
	Goal() {}
	Goal(int x, int y) {
		pos.x = x;
		pos.y = y;
	}
	sf::Vector2i pos;

	bool isTouching(Player * p) {
		double xdist = abs(pos.x - p->p.x);
		double ydist = abs(pos.y - p->p.y);
		double dist = sqrt(xdist*xdist + ydist*ydist);
		return dist <= goal_size + playersize;
	}

	sf::CircleShape handle() {
		sf::CircleShape c;
		c.setFillColor(sf::Color::White);
		c.setPosition(pos.x-goal_size, pos.y-goal_size);
		c.setRadius(goal_size);
		return c;
	}

};

#endif