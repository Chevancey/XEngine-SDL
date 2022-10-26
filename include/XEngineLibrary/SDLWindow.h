#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include <LIB_COMPILING.h>

class LIB_API SDLWindow
{
public:
	SDLWindow(const std::string& WindowName, int Width, int Height);
	SDLWindow(const std::string& WindowName, Uint32 flags);
	SDLWindow(const std::string& WindowName, int PosX, int PosY, int Width, int Height, Uint32 flags);
	SDLWindow(const SDLWindow&) = delete;

	

	~SDLWindow();

	SDL_Window* get();
	int GetWindowSizeX();
	int GetWindowSizeY();

	SDLWindow& operator = (const SDLWindow&) = delete;
private:

	SDL_Window* m_window;
	int m_sizeX, m_sizeY;
};