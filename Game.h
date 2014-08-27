#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Level.h"
#include "Parser.h"

#define WIDTH 1000.0
#define HEIGHT 600.0

#define IS lev->_state == 
#define ISNT lev->_state !=
#define SET lev->_state =
#define _ball lev->_dot
#define SLINGSHOT_LEN 50
#define SPRING 0.005
#define dotsize 2
#define textsize 15
#define bounds_checking false
#define zoom_view true
#define crashing false

class Game {
public:

	void init(sf::RenderWindow * window);
	sf::RenderWindow * _window;
	sf::Font font;
	Level * lev;
	float factor;

	void update();
	void draw(), drawText();
	void pause(), resume(), crash(), win();
	void move();
	void check_bounds();
	void drawDot(sf::Color c, float xp, float yp);
	bool nextLevel();

	static const std::vector<sf::Color> _colors;

private:
	std::vector<Level> _levels;
};

#endif