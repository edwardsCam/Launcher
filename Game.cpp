#include "Game.h"

const std::vector<sf::Color> Game::_colors = Parser::parseColors();

void Game::init(sf::RenderWindow * window) {
	_window = window;
	_levels = Parser::parseLevels();
	font.loadFromFile("arial.ttf");
	factor = 1.0;
	if (_levels.size()) {
		act_lev = &_levels[0];
		act_lev->active = true;
	} else
		act_lev = NULL;
}

bool Game::nextLevel() {
	if (act_lev == NULL)
		return false;
	if (act_lev->id == _levels.size()) {
		act_lev = NULL;
		return false;
	} else {
		act_lev = &(_levels[act_lev->id]);
		return true;
	}
}

bool Game::isPaused() {
	return act_lev->_state == PAUSED;
}

void Game::pause() {
	act_lev->_pstate = act_lev->_state;
	act_lev->_state = PAUSED;
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(40);
	t.setColor(sf::Color::Red);
	t.setStyle(sf::Text::Style::Bold);
	t.setPosition(300, 200);
	t.setString("PAUSED");
	_window->draw(t);
}

void Game::resume() {
	act_lev->_state = act_lev->_pstate;
}

void Game::crash() {
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(40);
	t.setColor(sf::Color::Red);
	t.setStyle(sf::Text::Style::Bold);
	t.setPosition(300, 200);
	t.setString("CRASHED");
	_window->draw(t);
}

void Game::drawDot(sf::Color c, float xp, float yp) {
	sf::CircleShape dot;
	dot.setPosition(xp - dotsize, yp - dotsize);
	dot.setFillColor(c);
	dot.setRadius(dotsize);
	_window->draw(dot);
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(10);
	t.setColor(c);
	t.setPosition(xp+5, yp-8);
	t.setString("(" + std::to_string((int)xp) + ", " + std::to_string((int)yp) + ")");
	_window->draw(t);
}

void Game::draw() {
	for (unsigned int i = 0; i < act_lev->nPlanets; i++)
		_window->draw(act_lev->drawPlanet(i));

	for (unsigned int i = 1; i < active_level pstream.size(); i++) {
		if (i == 1)
			drawDot(sf::Color::White, active_level pstream[0].position.x, active_level pstream[0].position.y);
		sf::Vertex line2[2] = {active_level pstream[i-1], active_level pstream[i]};
		line2[0].color = sf::Color::White;
		line2[1].color = sf::Color::White;
		_window->draw(line2, 2, sf::Lines);
	}

	for (unsigned int i = 1; i < active_level stream.size(); i++) {
		sf::Vertex line1[2] = {active_level stream[i-1], active_level stream[i]};
		_window->draw(line1, 2, sf::Lines);
	}
	if (act_lev->released)
		drawDot(sf::Color::Black, act_lev->x_r, act_lev->y_r);

	if (IS INITIAL_READY || IS DRAGGING || IS LAUNCHING) {
		double a;
		int x1 = act_lev->x_i;
		int y1 = act_lev->y_i;
		int x2 = _ball.p.x;
		int y2 = _ball.p.y;
		int xdiff = x2 - x1;
		if (xdiff == 0)
			a = 0.0;
		else {
			int ydiff = y2 - y1;
			a = atan((double)xdiff/ydiff);
		}
		sf::Vertex v1, v2, v3;
		v1.position = sf::Vector2f(x1 + cos(a) * SLINGSHOT_LEN, y1 - sin(a) * SLINGSHOT_LEN);
		v2.position = sf::Vector2f(_ball.p.x, _ball.p.y);
		v3.position = sf::Vector2f(x1 - cos(a) * SLINGSHOT_LEN, y1 + sin(a) * SLINGSHOT_LEN);
		v1.color = sf::Color::Red;
		v2.color = sf::Color::Red;
		v3.color = sf::Color::Red;
		sf::Vertex line1[2] = {v1, v2};
		sf::Vertex line2[2] = {v2, v3};
		_window->draw(line1, 2, sf::Lines);
		_window->draw(line2, 2, sf::Lines);
	}
	_window->draw(act_lev->drawPlayer());
}

float max(float a, float b) {
	if (a >= b)
		return a;
	else
		return b;
}

float min(float a, float b) {
	if (a <= b)
		return a;
	else
		return b;
}

void Game::drawText() {
	sf::Text t;
	t.setFont(font);
	int textScale = (double)textsize * (abs((WIDTH - 2*playersize)-_ball.p.x)) / (WIDTH - 2*playersize);
	t.setCharacterSize(textScale);
	t.setColor(sf::Color::Red);
	t.setPosition(0, 0);
	float xv = act_lev->_dot.v.x;
	float yv = act_lev->_dot.v.y;
	t.setString("Speed: " + std::to_string((int)sqrt(xv*xv + yv*yv)));
	_window->draw(t);
	if (IS DRAGGING) {
		sf::Text t;
		t.setFont(font);
		int textScale = (double)(textsize-3) * (abs((WIDTH - 2*playersize)-_ball.p.x)) / (WIDTH - 2*playersize);
		t.setCharacterSize(textScale);
		t.setColor(sf::Color::Black);
		sf::Vector2i mpos = sf::Mouse::getPosition(*_window);
		t.setPosition(mpos.x + playersize, mpos.y - playersize);
		t.setString("(" + std::to_string(mpos.x) + ", " + std::to_string(mpos.y) + ")");
		_window->draw(t);
	}
}

void Game::check_bounds() {
	if (_ball.p.x < playersize)
		_ball.p.x = playersize;
	if (_ball.p.y < playersize)
		_ball.p.y = playersize;
	if (_ball.p.x > WIDTH - playersize)
		_ball.p.x = WIDTH - playersize;
	if (_ball.p.y > HEIGHT - playersize)
		_ball.p.y = HEIGHT - playersize;
}

void Game::move() {
	Player * p = &act_lev->_dot;
	unsigned int ix = p->p.x;
	unsigned int iy = p->p.y;
	p->v.x += p->a.x;
	p->v.y += p->a.y;
	p->x_speed_buff += p->v.x;
	p->y_speed_buff += p->v.y;
	if (p->x_speed_buff >= 1 || p->x_speed_buff <= -1) {
		int s = (int)p->x_speed_buff;
		p->p.x += s;
		p->x_speed_buff -= s;
	}
	if (p->y_speed_buff >= 1 || p->y_speed_buff <= -1) {
		int s = (int)p->y_speed_buff;
		p->p.y += s;
		p->y_speed_buff -= s;
	}
	if (bounds_checking)
		check_bounds();
	if (ix != p->p.x || iy != p->p.y) {
		sf::Vertex v;
		v.position = sf::Vector2f(p->p.x, p->p.y);
		v.color = sf::Color::Black;
		active_level stream.push_back(v);
	}
	if (!bounds_checking && zoom_view) {
		factor = 1.0;
		if (_ball.p.x < playersize) {
			int diff = WIDTH - playersize - _ball.p.x;
			factor = (double)diff/(WIDTH - (2*playersize));
		}
		else if (_ball.p.x > WIDTH - playersize) {
			int diff = _ball.p.x - playersize;
			factor = (double)diff/(WIDTH - (2*playersize));
		}

		if (_ball.p.y < playersize) {
			int diff = HEIGHT - playersize - _ball.p.y;
			factor = max(factor, (double)diff/(HEIGHT - (2*playersize)));
		}
		else if (_ball.p.y > HEIGHT - playersize) {
			int diff = _ball.p.y - playersize;
			factor = max(factor, (double)diff/(HEIGHT - (2*playersize)));
		}
	}
}

void Game::update() {
	if (IS DRAGGING) {
		sf::Vector2i mpos = sf::Mouse::getPosition(*_window);
		act_lev->setPlayerPos(mpos.x, mpos.y);
		return;
	}
	else if (IS LAUNCHING) {
		if (!act_lev->released) {
			act_lev->x_r = _ball.p.x;
			act_lev->y_r = _ball.p.y;
			act_lev->released = true;
			sf::Vertex v;
			v.position.x = _ball.p.x;
			v.position.y = _ball.p.y;
			active_level stream.push_back(v);
		}
		bool left = _ball.p.x < act_lev->x_i;
		int distx, disty;
		distx = act_lev->x_i - _ball.p.x;
		disty = act_lev->y_i - _ball.p.y;
		double ax, ay;
		ax = (double)distx * SPRING;
		ay = (double)disty * SPRING;
		_ball.a.x = ax;
		_ball.a.y = ay;
		move();
		if (left) {
			if (_ball.p.x >= act_lev->x_i)
				SET IN_PLAY;
		} else {
			if (_ball.p.x <= act_lev->x_i)
				SET IN_PLAY;
		}
	}
	else if (IS IN_PLAY) {
		sf::Vector2f pull = act_lev->getGravitationalPull();
		_ball.a.x = pull.x;
		_ball.a.y = pull.y;
		move();
		if (crashing && act_lev->isCrashed()) {
			SET CRASHED;
			return;
		}
	} else if (IS CRASHED) {
		crash();
	}
}