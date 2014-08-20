// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Game.h"
#include "Planet.h"

// Globals


// Definitions
#define MAX_FRAMERATE 24
#define WIDTH 800
#define HEIGHT 600
#define BG_COLOR 175,220,220
#define IS curr->_state == 

void draw(sf::RenderWindow * window, Game * theGame) {
	window->clear(sf::Color(BG_COLOR));
	theGame->current_level->drawPlanets(window);
	theGame->current_level->drawPlayer(window);
	window->display();
}

void update(sf::RenderWindow * window, Level* curr) {
	if (IS DRAGGING) {
		sf::Vector2i mpos = sf::Mouse::getPosition(*window);
		curr->setPlayerPos(mpos.x-15, mpos.y-15);
	}
	if (curr->_player.pos.x < 0)
		curr->_player.pos.x = 0;
	if (curr->_player.pos.y < 0)
		curr->_player.pos.y = 0;
	if (curr->_player.pos.x > 770)
		curr->_player.pos.x = 770;
	if (curr->_player.pos.y > 570)
		curr->_player.pos.y = 570;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Planet Launcher");
	window.setFramerateLimit(MAX_FRAMERATE);
	window.setKeyRepeatEnabled(false);
	window.clear(sf::Color(BG_COLOR));

	Game theGame;
	theGame.init(&window);

	//game loop
	while (window.isOpen())
	{
		Level * curr = theGame.current_level;
		while (curr && curr->active)
		{
			sf::Event event;
			while (window.pollEvent(event)) {
				switch (event.type) {
				case (sf::Event::Closed):
					{
						//todo save state? or other things before closing
						curr->active = false;
						window.close();
						break;
					}
				case (sf::Event::LostFocus):
					{
						theGame.pause();
						break;
					}
				case (sf::Event::GainedFocus):
					{
						theGame.resume();
						break;
					}
				case (sf::Event::Resized):
					{
						sf::Vector2u s(WIDTH, HEIGHT);
						window.setSize(s);
						break;
					}
				case (sf::Event::KeyPressed):
					{
						//todo
						if (event.key.code == sf::Keyboard::Escape) {

						}
						else if (event.key.code == sf::Keyboard::Space) {
							if (theGame.isPaused())
								theGame.resume();
							else
								theGame.pause();
						}
						break;
					}
				case (sf::Event::MouseButtonPressed):
					{
						//todo
						sf::Vector2i playerpos = curr->_player.pos;
						while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							sf::Vector2i mousepos = sf::Mouse::getPosition(window);
							if ((mousepos.x - playerpos.x) < 30 && (mousepos.y - playerpos.y) < 30) {
								curr->_state = DRAGGING;
								break;
							}
						}
						break;
					}
				case (sf::Event::MouseButtonReleased):
					{
						if (IS DRAGGING)
							curr->_state = LAUNCHING;
						break;
					}
					//todo: other events
				} // switch
			} // event poll loop
			update(&window, curr);
			draw(&window, &theGame);
		} // level loop
		if (!theGame.nextLevel())
			window.close();
	} // game loop

	return 0;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return 0;
}