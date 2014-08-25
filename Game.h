#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include "Level.h"
#include "Parser.h"

#define IS current_level->_state == 
#define ISNT current_level->_state !=
#define SET current_level->_state =
#define _ball current_level->_player
#define SLINGSHOT_LEN 50
#define SPRING 0.005
#define dotsize 2
#define textsize 15
#define bounds_checking false
#define zoom_view true

class Game {
public:

	static const std::vector<sf::Color> _colors;
	void init(sf::RenderWindow * window);
	sf::RenderWindow * _window;
	sf::Font font;

	int xmin, ymin, xmax, ymax;
	float factor;

	std::vector<sf::Vertex> stream;

	Level * current_level;
	bool nextLevel();

	bool isPaused();
	void pause();
	void resume();
	void move();
	void check_bounds();
	void update();
	void draw();
	void drawText();

private:
	std::vector<Level> _levels;
};

#endif