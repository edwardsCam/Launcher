#include "Level.h"
#include "Parser.h"
#include "Game.h"

#define color _colors[i]

Level::Level() {
	Goal g();
	active = false;
	released = false;
	_state = INITIAL_READY;
	_pstate = INITIAL_READY;
}

sf::CircleShape Level::drawPlanet(unsigned int i) {
	Planet thePlanet = _planets[i];
	float r = thePlanet.radius;
	sf::CircleShape circle(r);
	circle.setPosition(thePlanet.xpos-r, thePlanet.ypos-r);
	circle.setFillColor(sf::Color(Game::color));
	return circle;
}

sf::CircleShape Level::drawPlayer() {
	sf::CircleShape circle(playersize);
	circle.setPosition((float)_dot.p.x-playersize, (float)_dot.p.y-playersize);
	circle.setFillColor(sf::Color::Black);
	return circle;
}

void Level::reset() {
	active = true;
	released = false;
	_state = INITIAL_READY;
	_pstate = INITIAL_READY;
	_dot.a.x = 0;
	_dot.a.y = 0;
	_dot.v.x = 0;
	_dot.v.y = 0;
	_dot.p.x = x_i;
	_dot.p.y = y_i;
	x_r = x_i;
	y_r = y_i;
	pstream = stream;
	stream.clear();
}

void Level::addPlanet(Planet p) {
	_planets.push_back(p);
	nPlanets = _planets.size();
}

void Level::setPlayerPos(sf::Vector2i pos) {
	_dot.p = pos;
}

void Level::setPlayerPos(int x, int y) {
	_dot.p.x = x;
	_dot.p.y = y;
}

Planet * Level::planetAt(int i) {
	return &_planets[i];
}

sf::Vector2f Level::getGravitationalPull() {
	float sumx = 0;
	float sumy = 0;
	for (unsigned int i = 0; i < nPlanets; i++) {
		sf::Vector2f a = (&_planets[i])->getPull(_dot.p);
		sumx += a.x;
		sumy += a.y;
	}
	return sf::Vector2f(sumx, sumy);
}

bool Level::isCrashed() {
	for (unsigned int i = 0; i < _planets.size(); i++) {
		double xd = _dot.p.x - _planets[i].xpos;
		double yd = _dot.p.y - _planets[i].ypos;
		if (sqrt(xd*xd + yd*yd) < _planets[i].radius)
			return true;
	}
	return false;
}