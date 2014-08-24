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