#include "Level.h"
#include "Parser.h"
#include "Game.h"

#define color _colors[i]

Level::Level() {
	active = false;
	_state = INITIAL_READY;
}

sf::Vector2u Level::getPlayerPos() {
	return _player.pos;
}

void Level::drawPlanets(sf::RenderWindow * window) {
	for (int i = 0; i < _planets.size(); i++) {
		Planet thePlanet = _planets[i];
		sf::CircleShape circle(thePlanet.radius);
		circle.setPosition(thePlanet.xpos, thePlanet.ypos);
		circle.setFillColor(sf::Color(Game::color));
		window->draw(circle);
	}
}

void Level::drawPlayer(sf::RenderWindow * window) {
	sf::CircleShape circle(15);
	circle.setPosition(_player.pos.x, _player.pos.y);
	circle.setFillColor(sf::Color::Black);
	window->draw(circle);
}

void Level::addPlanet(Planet p) {
	_planets.push_back(p);
}

void Level::setPlayerPos(sf::Vector2u pos) {
	_player.pos = pos;
}

void Level::setPlayerPos(unsigned int x, unsigned int y) {
	_player.pos.x = x;
	_player.pos.y = y;
}