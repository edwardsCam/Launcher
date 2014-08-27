#include "Game.h"

const std::vector<sf::Color> Game::_colors = Parser::parseColors();

void Game::init(sf::RenderWindow * window) {
	_window = window;
	_levels = Parser::parseLevels();
	font.loadFromFile("arial.ttf");
	factor = 1.0;
	if (_levels.size()) {
		lev = &_levels[0];
		lev->active = true;
	} else
		lev = NULL;
}

bool Game::nextLevel() {
	if (lev == NULL)
		return false;
	if (lev->id >= _levels.size()) {
		lev = NULL;
		return false;
	} else {
		lev = &(_levels[lev->id]);
		return true;
	}
}

void Game::pause() {
	lev->_pstate = lev->_state;
	lev->_state = PAUSED;
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
	lev->_state = lev->_pstate;
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

void Game::win() {
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(40);
	t.setColor(sf::Color::Red);
	t.setStyle(sf::Text::Style::Bold);
	t.setPosition(300, 200);
	t.setString("WON");
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
	t.setCharacterSize((double)(textsize-4) * factor);
	t.setColor(c);
	t.setPosition(xp+5, yp-8);
	t.setString("(" + std::to_string((int)xp) + ", " + std::to_string((int)yp) + ")");
	_window->draw(t);
}

void Game::draw() {
	for (unsigned int i = 0; i < lev->nPlanets; i++)
		_window->draw(lev->planetHandle(i));
	_window->draw(lev->goal.handle());

	for (unsigned int i = 1; i < lev->pstream.size(); i++) {
		if (i == 1)
			drawDot(sf::Color::White, lev->pstream[0].position.x, lev->pstream[0].position.y);
		sf::Vertex line[2] = {lev->pstream[i-1], lev->pstream[i]};
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		_window->draw(line, 2, sf::Lines);
	}

	for (unsigned int i = 1; i < lev->stream.size(); i++) {
		sf::Vertex line1[2] = {lev->stream[i-1], lev->stream[i]};
		_window->draw(line1, 2, sf::Lines);
	}
	if (lev->released)
		drawDot(sf::Color::Black, lev->x_r, lev->y_r);

	if (IS INITIAL_READY || IS DRAGGING || IS LAUNCHING) {
		double ang;
		int x1 = lev->x_i;
		int y1 = lev->y_i;
		int x2 = _ball.p.x;
		int y2 = _ball.p.y;
		int xdiff = x2 - x1;
		if (xdiff == 0)
			ang = 0.0;
		else {
			int ydiff = y2 - y1;
			ang = atan((double)xdiff/ydiff);
		}
		sf::Vertex v1, v2, v3;
		v2.position = sf::Vector2f(_ball.p.x, _ball.p.y);
		v1.position = sf::Vector2f(x1 + cos(ang) * SLINGSHOT_LEN, y1 - sin(ang) * SLINGSHOT_LEN);
		v3.position = sf::Vector2f(x1 - cos(ang) * SLINGSHOT_LEN, y1 + sin(ang) * SLINGSHOT_LEN);
		v1.color = sf::Color::Red;
		v2.color = sf::Color::Red;
		v3.color = sf::Color::Red;
		sf::Vertex line1[2] = {v1, v2};
		sf::Vertex line2[2] = {v2, v3};
		_window->draw(line1, 2, sf::Lines);
		_window->draw(line2, 2, sf::Lines);
	}
	_window->draw(lev->playerHandle());
}

void Game::drawText() {
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(textsize-3);
	t.setColor(sf::Color::Black);
	sf::Vector2i mpos = sf::Mouse::getPosition(*_window);
	t.setPosition(mpos.x + playersize, mpos.y - playersize);
	t.setString("(" + std::to_string(mpos.x) + ", " + std::to_string(mpos.y) + ")");
	_window->draw(t);
}

void Game::check_bounds() {
	if (_ball.p.x < playersize)
		_ball.p.x = playersize;
	if (_ball.p.y < playersize)
		_ball.p.y = playersize;
	if (_ball.p.x > (int)WIDTH - playersize)
		_ball.p.x = (int)WIDTH - playersize;
	if (_ball.p.y > (int)HEIGHT - playersize)
		_ball.p.y = (int)HEIGHT - playersize;
}

float max(float a, float b) {
	if (a >= b)
		return a;
	else
		return b;
}

void Game::move() {
	Player * p = &lev->_dot;
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
		lev->stream.push_back(v);
	}
	if (!bounds_checking && zoom_view) {
		factor = 1.0;
		if (_ball.p.x < playersize)
			factor = (WIDTH - playersize - _ball.p.x)/(WIDTH - 2*playersize);
		else if (_ball.p.x > WIDTH - playersize)
			factor = (_ball.p.x - playersize)/(WIDTH - 2*playersize);

		if (_ball.p.y < playersize)
			factor = max( factor, (HEIGHT - playersize - _ball.p.y)/(HEIGHT - 2*playersize) );
		else if (_ball.p.y > HEIGHT - playersize)
			factor = max( factor, (_ball.p.y - playersize)/(HEIGHT - 2*playersize) );
	}
}

void Game::update() {
	if (IS DRAGGING) {
		sf::Vector2i mpos = sf::Mouse::getPosition(*_window);
		lev->setPlayerPos(mpos.x, mpos.y);
		return;
	}
	else if (IS LAUNCHING) {
		if (!lev->released) {
			lev->released = true;
			lev->x_r = _ball.p.x;
			lev->y_r = _ball.p.y;
			sf::Vertex v;
			v.position.x = _ball.p.x;
			v.position.y = _ball.p.y;
			lev->stream.push_back(v);
		}
		bool left = _ball.p.x < lev->x_i;
		int distx, disty;
		distx = lev->x_i - _ball.p.x;
		disty = lev->y_i - _ball.p.y;
		_ball.a.x = (double)distx * SPRING;
		_ball.a.y = (double)disty * SPRING;
		move();

		if (left) {
			if (_ball.p.x >= lev->x_i)
				SET IN_PLAY;
		} else {
			if (_ball.p.x <= lev->x_i)
				SET IN_PLAY;
		}
	}
	else if (IS IN_PLAY) {
		sf::Vector2f pull = lev->getGravitationalPull();
		_ball.a.x = pull.x;
		_ball.a.y = pull.y;
		move();

		if (lev->goal.isTouching(&_ball)) {
			SET WON;
			return;
		}
		if (crashing && lev->isCrashed()) {
			SET CRASHED;
			return;
		}
	} else if (IS CRASHED)
		crash();
	else if (IS WON)
		win();
}