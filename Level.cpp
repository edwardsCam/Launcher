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

void Level::drawPlanets(sf::RenderWindow * window) {
	numPlanets = _planets.size();
	for (unsigned int i = 0; i < numPlanets; i++) {
		Planet thePlanet = _planets[i];
		float r = thePlanet.radius;
		sf::CircleShape circle(r);
		circle.setPosition(thePlanet.xpos-r, thePlanet.ypos-r);
		circle.setFillColor(sf::Color(Game::color));
		window->draw(circle);
	}
}

void Level::drawPlayer(sf::RenderWindow * window) {
	sf::CircleShape circle(15);
	circle.setPosition((float)_player.p.x-15, (float)_player.p.y-15);
	circle.setFillColor(sf::Color::Black);
	window->draw(circle);
}

void Level::movePlayer(int x, int y) {
	_player.p.x += x;
	_player.p.y += y;
}

void Level::addPlanet(Planet p) {
	_planets.push_back(p);
}

void Level::setPlayerPos(sf::Vector2u pos) {
	_player.p = pos;
}

void Level::setPlayerPos(unsigned int x, unsigned int y) {
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