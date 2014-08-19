#include "Level.h"

sf::Vector2u Level::getPlayerPos() {
	return _player.pos;
}

void Level::drawPlanets(sf::RenderWindow window) {
	for (int i = 0; i < _planets.size(); i++) {
		PlanetInfo thePlanet = _planets[i];
		sf::CircleShape shape(thePlanet.p.radius);
		shape.setPosition(thePlanet.xpos, thePlanet.ypos);
		shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		window.draw(shape);
	}
}