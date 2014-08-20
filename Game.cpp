#include "Game.h"

const std::vector<sf::Color> Game::_colors = Parser::parseColors();

void Game::init(sf::RenderWindow * window) {
	_window = window;
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
	current_level->_state = PAUSED;
}

void Game::resume() {

}