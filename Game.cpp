#include "Game.h"

const std::vector<sf::Color> Game::_colors = Parser::parseColors();

void Game::init(sf::RenderWindow * window) {
	_window = window;
	font.loadFromFile("arial.ttf");
	_levels = Parser::parseLevels();	
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
	current_level->drawPlanets(_window);
	current_level->drawPlayer(_window);
}

void Game::drawText() {
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(15);
	t.setColor(sf::Color::Red);
	t.setPosition(0, 0);
	t.setString(std::to_string(sf::Mouse::getPosition(*_window).x) + ", " + std::to_string(sf::Mouse::getPosition(*_window).y));
	_window->draw(t);
	t.setColor(sf::Color::Green);
	t.setPosition(0, 18);
	t.setString(std::to_string(current_level->_player.p.x) + ", " + std::to_string(current_level->_player.p.y));
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

void m(Player * p) {
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
}

void Game::update() {
	if (IS DRAGGING) {
		sf::Vector2i mpos = sf::Mouse::getPosition(*_window);
		current_level->setPlayerPos(mpos.x, mpos.y);
	}
	else if (IS LAUNCHING) {
		bool left = _ball.p.x < current_level->initx;
		int distx, disty;
		distx = current_level->initx - _ball.p.x;
		disty = current_level->inity - _ball.p.y;
		double ax, ay;
		ax = (double)distx * SPRING;
		ay = (double)disty * SPRING;
		_ball.a.x = ax;
		_ball.a.y = ay;
		m(&_ball);
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
		m(&_ball);
	}
	check_bounds();
}