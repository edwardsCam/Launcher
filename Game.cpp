#include "Game.h"

const std::vector<sf::Color> Game::_colors = Parser::parseColors();

void Game::init(sf::RenderWindow * window) {
	_window = window;
	_levels = Parser::parseLevels();
	font.loadFromFile("arial.ttf");
	xmin = 15;
	ymin = 15;
	xmax = 800 - 15;
	ymax = 600 - 15;
	factorX = 1;
	factorY = 1;
	if (_levels.size()) {
		current_level = &_levels[0];
		current_level->active = true;
	} else
		current_level = NULL;
}

bool Game::nextLevel() {
	if (current_level == NULL)
		return false;
	if (current_level->id == _levels.size()) {
		current_level = NULL;
		return false;
	} else {
		current_level = &(_levels[current_level->id]);
		return true;
	}
}

bool Game::isPaused() {
	return current_level->_state == PAUSED;
}

void Game::pause() {
	current_level->_prevstate = current_level->_state;
	current_level->_state = PAUSED;
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
	current_level->_state = current_level->_prevstate;
}

void Game::draw() {
	for (unsigned int i = 0; i < current_level->numPlanets; i++)
		_window->draw(current_level->drawPlanet(i));

	for (unsigned int i = 1; i < stream.size(); i++) {
		sf::Vertex line[2] = {stream[i-1], stream[i]};
		_window->draw(line, 2, sf::Lines);
	}
	if (current_level->released) {
		sf::CircleShape dot;
		dot.setPosition(current_level->releasex-dotsize, current_level->releasey-dotsize);
		dot.setFillColor(sf::Color::Black);
		dot.setRadius(dotsize);
		_window->draw(dot);
		sf::Text t;
		t.setFont(font);
		t.setCharacterSize(10);
		t.setColor(sf::Color::Black);
		t.setPosition(current_level->releasex+5, current_level->releasey-8);
		t.setString("(" + std::to_string(current_level->releasex) + ", " + std::to_string(current_level->releasey) + ")");
		_window->draw(t);
	}
	if (IS INITIAL_READY || IS DRAGGING || IS LAUNCHING) {
		unsigned int a = current_level->start_angle;
		unsigned int x1 = current_level->initx;
		unsigned int y1 = current_level->inity;
		sf::Vertex v1, v2, v3;
		v2.position = sf::Vector2f(_ball.p.x, _ball.p.y);
		v1.position = sf::Vector2f(x1 - cos(a) * SLINGSHOT_LEN, y1 - sin(a) * SLINGSHOT_LEN);
		v3.position = sf::Vector2f(x1 + cos(a) * SLINGSHOT_LEN, y1 + sin(a) * SLINGSHOT_LEN);
		v1.color = sf::Color::Red;
		v2.color = sf::Color::Red;
		v3.color = sf::Color::Red;
		sf::Vertex line1[2] = {v1, v2};
		sf::Vertex line2[2] = {v2, v3};
		_window->draw(line1, 2, sf::Lines);
		_window->draw(line2, 2, sf::Lines);
	}
	_window->draw(current_level->drawPlayer());
}

void Game::drawText() {
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(15);
	t.setColor(sf::Color::Red);
	t.setPosition(800 - (xmax - xmin), 600 - (ymax - ymin));
	sf::Vector2i mpos = sf::Mouse::getPosition(*_window);
	t.setString("(" + std::to_string(mpos.x) + ", " + std::to_string(mpos.y) + ")");
	_window->draw(t);
	t.setColor(sf::Color::Black);
	t.setPosition(xmin, ymin + 18);
	t.setString("(" + std::to_string(current_level->_player.p.x) + ", " + std::to_string(current_level->_player.p.y) + ")");
	_window->draw(t);
}

void Game::check_bounds() {
	if (_ball.p.x < 15)
		_ball.p.x = 15;
	if (_ball.p.y < 15)
		_ball.p.y = 15;
	if (_ball.p.x > 785)
		_ball.p.x = 785;
	if (_ball.p.y > 585)
		_ball.p.y = 585;
}

void Game::move() {
	Player * p = &current_level->_player;
	unsigned int ix = p->p.x;
	unsigned int iy = p->p.y;
	p->v.x += p->a.x;
	p->v.y += p->a.y;
	p->speed_bufferx += p->v.x;
	p->speed_buffery += p->v.y;
	if (p->speed_bufferx >= 1 || p->speed_bufferx <= -1) {
		int s = (int)p->speed_bufferx;
		p->p.x += s;
		p->speed_bufferx -= s;
	}
	if (p->speed_buffery >= 1 || p->speed_buffery <= -1) {
		int s = (int)p->speed_buffery;
		p->p.y += s;
		p->speed_buffery -= s;
		
	}
	if (ix != p->p.x || iy != p->p.y) {
		sf::Vertex v;
		v.position = sf::Vector2f(p->p.x, p->p.y);
		v.color = sf::Color::Black;
		stream.push_back(v);
	}
}

void Game::update() {
	if (IS DRAGGING) {
		sf::Vector2i mpos = sf::Mouse::getPosition(*_window);
		current_level->setPlayerPos(mpos.x, mpos.y);
	}
	else if (IS LAUNCHING) {
		if (!current_level->released) {
			current_level->releasex = _ball.p.x;
			current_level->releasey = _ball.p.y;
			current_level->released = true;
			sf::Vertex v;
			v.position.x = _ball.p.x;
			v.position.y = _ball.p.y;
			stream.push_back(v);
		}
		bool left = _ball.p.x < current_level->initx;
		int distx, disty;
		distx = current_level->initx - _ball.p.x;
		disty = current_level->inity - _ball.p.y;
		double ax, ay;
		ax = (double)distx * SPRING;
		ay = (double)disty * SPRING;
		_ball.a.x = ax;
		_ball.a.y = ay;
		move();
		if (left) {
			if (_ball.p.x >= current_level->initx)
				SET IN_PLAY;
		} else {
			if (_ball.p.x <= current_level->initx)
				SET IN_PLAY;
		}
	}
	else if (IS IN_PLAY) {
		sf::Vector2f pull = current_level->getGravitationalPull();
		_ball.a.x = pull.x;
		_ball.a.y = pull.y;
		move();
	}
	if (bounds_checking)
		check_bounds();
	if (zoom_view) {
		if (_ball.p.x > xmax) {
			double init = (xmax - xmin);
			xmax = _ball.p.x;
			factorX = (double)(xmax - xmin) / init;
		}
		else if (_ball.p.x < xmin) {
			double init = (xmax - xmin);
			xmin = _ball.p.x;
			factorX = (double)(xmax - xmin) / init;
		} else
			factorX = 1.0;

		if (_ball.p.y > ymax) {
			double init = (ymax - ymin);
			ymax = _ball.p.y;
			factorY = (double)(ymax - ymin) / init;
		}
		else if (_ball.p.y < ymin) {
			double init = (ymax - ymin);
			ymin = _ball.p.y;
			factorY = (double)(ymax - ymin) / init;
		}
		else factorY = 1.0;
	}
}