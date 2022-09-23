#include "SDLWindow.h"

SDLWindow::SDLWindow(const std::string& WindowName, int Width, int Height) :
SDLWindow(WindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0)
{
}

SDLWindow::SDLWindow(const std::string& WindowName, Uint32 flags) :
	SDLWindow(WindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 720, flags)
{
}

SDLWindow::SDLWindow(const std::string& WindowName, int PosX, int PosY, int Width, int Height, Uint32 flags)
{
	m_window = SDL_CreateWindow(WindowName.c_str(), PosX, PosY, Width, Height, flags);

	SDL_GetWindowSize(m_window, &m_sizeX, &m_sizeY);
	//std::cout << m_sizeX << " | " << m_sizeY << std::endl;
}

int SDLWindow::GetWindowSizeX()
{
	return m_sizeX;
}

int SDLWindow::GetWindowSizeY()
{
	return m_sizeY;
}


SDLWindow::~SDLWindow()
{
	SDL_DestroyWindow(m_window);
}


SDL_Window* SDLWindow::get()
{
	return m_window;
}