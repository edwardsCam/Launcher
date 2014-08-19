#include "Game.h"

bool Game::isPaused() {
	return _state == PAUSED;
}

void Game::pause() {
	_state = PAUSED;
}

void Game::resume() {

}

sf::Vector2u Game::getPlayerPos() {
	return _player.pos;
}