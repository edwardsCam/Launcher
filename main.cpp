// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

// Globals


// Definitions
#define MAX_FRAMERATE 24
#define WIDTH 800
#define HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Planet Launcher");
	window.setFramerateLimit(MAX_FRAMERATE);
	window.setKeyRepeatEnabled(false);

	//game loop
	while (window.isOpen())
	{	
		sf::Event event;
		while (window.pollEvent(event)) {

			switch (event.type)
			{
			case (sf::Event::Closed):
				{
					//todo save state? or other things before closing
					window.close();
					break;
				}

			case (sf::Event::LostFocus):
				{
					//todo
					//theGame.pause();
					break;
				}

			case (sf::Event::GainedFocus):
				{
					//todo
					//theGame.resume();
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
						/*
						if (theGame.isPaused())
							theGame.resume();
						else
							theGame.pause();
							*/
					}
					break;
				}

			case (sf::Event::MouseButtonPressed):
				{
					//todo
					break;
				}

				//todo: other events

			} // switch

		} // event poll loop

		window.clear(sf::Color::Black);

		//draw stuff here
		sf::CircleShape shape(50);

		// set the shape color to green
		shape.setFillColor(sf::Color(100, 250, 50));

		window.draw(shape);

		window.display();

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