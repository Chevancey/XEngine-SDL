#pragma once
#include <iostream>
#include <SDL.h>

class SDLpp
{
public:
	
	SDLpp();

	SDLpp(const SDLpp&) = delete;

	~SDLpp();

	SDLpp& operator = (const SDLpp&) = delete;

	//static bool PollEvent(SDL_Event* event);

	static bool PollEvent(SDL_Event* event);

private:
};