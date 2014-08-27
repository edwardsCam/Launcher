// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <string.h>
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Game.h"

// Definitions
#define MAX_FRAMERATE 32
#define BG_COLOR 175,220,220
#define _debug false
#define pause_on_lose_focus false

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
		Level * lev = theGame.lev;
		while (lev && lev->active)
		{
			sf::Event _event;
			if (window.pollEvent(_event)) {
				switch (_event.type) {
				case (sf::Event::Closed):
					{
						//todo save state? or other things before closing
						lev->active = false;
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
						window.setSize(sf::Vector2u(WIDTH, HEIGHT));
						break;
					}
				case (sf::Event::KeyPressed):
					{
						if (_event.key.code == sf::Keyboard::Return) {
							SET LAUNCHING;
						}
						else if (_event.key.code == sf::Keyboard::Space) {
							if (IS PAUSED)
								theGame.resume();
							else if (ISNT CRASHED && ISNT WON)
								theGame.pause();
						}
						else if (_event.key.code == sf::Keyboard::Escape) {
							lev->reset();
							theGame.factor = 1.0;
							view.setSize(WIDTH, HEIGHT);
							view.setCenter(WIDTH/2, HEIGHT/2);
							window.setView(view);
						}
						break;
					}
				case (sf::Event::MouseButtonPressed):
					{
						if (IS INITIAL_READY || IS DRAGGING || IS LAUNCHING) {
							sf::Vector2i playerpos = _ball.p;
							while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								sf::Vector2i mousepos = sf::Mouse::getPosition(window);
								if (abs(mousepos.x - playerpos.x) <= playersize && abs(mousepos.y - playerpos.y) <= playersize) {
									lev->_state = DRAGGING;
									break;
								}
							}
						}
						break;
					}
				case (sf::Event::MouseButtonReleased):
					{
						if (ISNT PAUSED && IS DRAGGING)
							lev->_state = LAUNCHING;
						break;
					}
				} // switch
			} // event poll
			if (ISNT PAUSED) {
				window.clear(sf::Color(BG_COLOR));
				theGame.update();
				theGame.draw();
			}
			if (zoom_view) {
				view.setSize(WIDTH, HEIGHT);
				view.zoom(theGame.factor);
				sf::Vector2i pos = theGame.lev->_dot.p;

				float xmid = WIDTH/2;
				float ymid = HEIGHT/2;
				float xcen = xmid;
				float ycen = ymid;

				if (pos.x < playersize)
					xcen = xmid - (playersize - pos.x)/2;
				else if (pos.x > WIDTH - playersize)
					xcen = xmid + (pos.x + playersize - WIDTH)/2;

				if (pos.y < playersize)
					ycen = ymid - (playersize - pos.y)/2;
				else if (pos.y > HEIGHT - playersize)
					ycen = ymid + (pos.y + playersize - HEIGHT)/2;

				view.setCenter(xcen, ycen);
				window.setView(view);
			}
			if (IS DRAGGING)
				theGame.drawText();
			window.display();
		} // level loop
		if (!theGame.nextLevel())
			window.close();
	} // game loop

	return 0;
}