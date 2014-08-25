#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Level.h"
#include "Parser.h"

#define IS current_level->_state == 
#define ISNT current_level->_state !=
#define SET current_level->_state =
#define _ball current_level->_player
#define SLINGSHOT_LEN 50
#define SPRING 0.005

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
	void check_bounds();
	void update();
	void draw();
	void drawText();

private:
	std::vector<Level> _levels;
};

#endif