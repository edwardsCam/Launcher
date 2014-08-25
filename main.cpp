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

#define _debug false
#define pause_on_lose_focus false

// Globals

// Definitions
#define MAX_FRAMERATE 32
#define WIDTH 800.0
#define HEIGHT 600.0
#define BG_COLOR 175,220,220
#define _ball curr->_player
#define IS curr->_state == 
#define ISNT curr->_state !=
#define SET curr->_state =

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Planet Launcher");
	window.setFramerateLimit(MAX_FRAMERATE);
	window.setKeyRepeatEnabled(false);
	window.clear(sf::Color(BG_COLOR));

	sf::View view(window.getDefaultView());

	Game theGame;
	theGame.init(&window);

	//game loop
	while (window.isOpen())
	{
		Level * curr = theGame.current_level;
		while (curr && curr->active)
		{
			sf::Event event;
			if (window.pollEvent(event)) {
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
						if (!_debug && pause_on_lose_focus)
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
							SET LAUNCHING;
						}
						else if (event.key.code == sf::Keyboard::Space) {
							if (theGame.isPaused())
								theGame.resume();
							else if (ISNT CRASHED)
								theGame.pause();
						}
						break;
					}
				case (sf::Event::MouseButtonPressed):
					{
						if (ISNT PAUSED && ISNT IN_PLAY) {
							sf::Vector2i playerpos = _ball.p;
							while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								sf::Vector2i mousepos = sf::Mouse::getPosition(window);
								if (abs(mousepos.x - playerpos.x) <= playersize && abs(mousepos.y - playerpos.y) <= playersize) {
									curr->_state = DRAGGING;
									break;
								}
							}
						}
						break;
					}
				case (sf::Event::MouseButtonReleased):
					{
						if (ISNT PAUSED) {
							if (IS DRAGGING)
								curr->_state = LAUNCHING;
						}
						break;
					}
					//todo: other events
				} // switch
			} // event poll
			if (ISNT PAUSED) {
				window.clear(sf::Color(BG_COLOR));
				theGame.update();
				theGame.draw();
			}
			if (zoom_view && theGame.factor > 1) {
				view.zoom(theGame.factor);
				view.setCenter((theGame.xmax + theGame.xmin)/2, (theGame.ymax + theGame.ymin)/2);
				window.setView(view);
			}
			theGame.drawText();
			window.display();
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