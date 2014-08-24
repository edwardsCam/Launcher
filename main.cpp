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

// Globals

// Definitions
#define MAX_FRAMERATE 32
#define WIDTH 800
#define HEIGHT 600
#define BG_COLOR 175,220,220
#define _ball curr->_player
#define IS curr->_state == 
#define ISNT curr->_state !=
#define SET curr->_state =
#define SLINGSHOT_LEN 50
#define SPRING 0.005

void draw(sf::RenderWindow * window, Level * curr) {
	if (IS INITIAL_READY || IS DRAGGING || IS LAUNCHING) {
		unsigned int a = curr->start_angle;
		unsigned int x1 = curr->initx;
		unsigned int y1 = curr->inity;
		sf::Vertex v1, v2, v3;
		v2.position = sf::Vector2f(_ball.p.x, _ball.p.y);
		v1.position = sf::Vector2f(x1 - cos(a) * SLINGSHOT_LEN, y1 - sin(a) * SLINGSHOT_LEN);
		v3.position = sf::Vector2f(x1 + cos(a) * SLINGSHOT_LEN, y1 + sin(a) * SLINGSHOT_LEN);
		v1.color = sf::Color::Red;
		v2.color = sf::Color::Red;
		v3.color = sf::Color::Red;
		sf::Vertex line1[2] = {v1, v2};
		sf::Vertex line2[2] = {v2, v3};
		window->draw(line1, 2, sf::Lines);
		window->draw(line2, 2, sf::Lines);
	}
	curr->drawPlanets(window);
	curr->drawPlayer(window);
}

void check_bounds(Level * curr) {
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

void update(sf::RenderWindow * window, Level* curr) {
	if (IS DRAGGING) {
		sf::Vector2i mpos = sf::Mouse::getPosition(*window);
		curr->setPlayerPos(mpos.x, mpos.y);
	}
	else if (IS LAUNCHING) {
		bool left = _ball.p.x < curr->initx;
		int distx, disty;
		distx = curr->initx - _ball.p.x;
		disty = curr->inity - _ball.p.y;
		double ax, ay;
		ax = (double)distx * SPRING;
		ay = (double)disty * SPRING;
		_ball.a.x = ax;
		_ball.a.y = ay;
		//sf::Vector2f pull = curr->getGravitationalPull();
		//_ball.a.x += pull.x;
		//_ball.a.y += pull.y;
		m(&_ball);
		if (left) {
			if (_ball.p.x >= curr->initx)
				SET IN_PLAY;
		} else {
			if (_ball.p.x <= curr->initx)
				SET IN_PLAY;
		}
	}
	else if (IS IN_PLAY) {
		sf::Vector2f pull = curr->getGravitationalPull();
		_ball.a.x = pull.x;
		_ball.a.y = pull.y;
		m(&_ball);
	}
	check_bounds(curr);
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
						if (!_debug)
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
							SET IN_PLAY;
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
						if (ISNT PAUSED && ISNT IN_PLAY) {
							sf::Vector2u playerpos = _ball.p;
							while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								sf::Vector2i mousepos = sf::Mouse::getPosition(window);
								if (abs(mousepos.x - (int)playerpos.x) <=15 && abs(mousepos.y - (int)playerpos.y) <= 15) {
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
			if (ISNT PAUSED)
				window.clear(sf::Color(BG_COLOR));
			update(&window, curr);
			draw(&window, curr);
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