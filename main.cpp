// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

// Global variables

unsigned int _width, _height;

// Definitions

#define MAX_FRAMERATE 24

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	_width = 800;
	_height = 600;

	sf::Window window;
	window.create(sf::VideoMode(_width, _height), "Planet Launcher");
	window.setFramerateLimit(MAX_FRAMERATE);

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

			case (sf::Event::Resized):
				{
					sf::Vector2u size = window.getSize();
					_width = size.x;
					_height = size.y;
					break;
				}

			case (sf::Event::KeyPressed):
				{
					//todo
					break;
				}

			case (sf::Event::MouseButtonPressed):
				{
					//todo
					break;
				}

				//todo: other events

			}
		}
	}

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

	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}