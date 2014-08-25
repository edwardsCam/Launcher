#include "Level.h"
#include "Parser.h"
#include "Game.h"

#define color _colors[i]

Level::Level() {
	active = false;
	released = false;
	_state = INITIAL_READY;
	_prevstate = INITIAL_READY;
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
	circle.setPosition((float)_player.p.x-playersize, (float)_player.p.y-playersize);
	circle.setFillColor(sf::Color::Black);
	return circle;
}

void Level::movePlayer(int x, int y) {
	_player.p.x += x;
	_player.p.y += y;
}

void Level::addPlanet(Planet p) {
	_planets.push_back(p);
	numPlanets = _planets.size();
}

void Level::setPlayerPos(sf::Vector2i pos) {
	_player.p = pos;
}

void Level::setPlayerPos(int x, int y) {
	_player.p.x = x;
	_player.p.y = y;
}

Planet * Level::planetAt(int i) {
	return &_planets[i];
}

sf::Vector2f Level::getGravitationalPull() {
	float sumx = 0;
	float sumy = 0;
	for (unsigned int i = 0; i < numPlanets; i++) {
		sf::Vector2f a = (&_planets[i])->getPull(_player.p);
		sumx += a.x;
		sumy += a.y;
	}
	return sf::Vector2f(sumx, sumy);
}

bool Level::isCrashed() {
	for (unsigned int i = 0; i < _planets.size(); i++) {
		double xd = _player.p.x - _planets[i].xpos;
		double yd = _player.p.y - _planets[i].ypos;
		if (sqrt(xd*xd + yd*yd) < _planets[i].radius)
			return true;
	}
	return false;
}