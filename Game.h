#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include "Level.h"
#include "Parser.h"

#define IS act_lev->_state == 
#define ISNT act_lev->_state !=
#define SET act_lev->_state =
#define _ball act_lev->_dot
#define active_level act_lev->
#define SLINGSHOT_LEN 50
#define SPRING 0.005
#define dotsize 2
#define textsize 15
#define bounds_checking false
#define zoom_view true
#define crashing true

class Game {
public:

	void init(sf::RenderWindow * window);
	sf::RenderWindow * _window;
	sf::Font font;

	int xmin, ymin, xmax, ymax;
	float factor;

	Level * act_lev;
	bool nextLevel();

	bool isPaused();
	void pause(), resume();
	void crash();
	void resetBounds();
	void move();
	void check_bounds();
	void update();
	void draw(), drawText();
	void drawDot(sf::Color c, float xp, float yp);

	static const std::vector<sf::Color> _colors;

private:
	std::vector<Level> _levels;
};

#endif