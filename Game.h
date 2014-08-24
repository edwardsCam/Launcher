#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Level.h"
#include "Parser.h"

class Game {
public:

	static const std::vector<sf::Color> _colors;
	void init(sf::RenderWindow * window);
	sf::RenderWindow * _window;
	sf::Font font;

	Level * current_level;
	bool nextLevel();

	bool isPaused();
	void pause();
	void resume();
	void drawText();

private:
	std::vector<Level> _levels;
};

#endif