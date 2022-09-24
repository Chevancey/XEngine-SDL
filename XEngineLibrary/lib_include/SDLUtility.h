#pragma once
#include <SDL.h>
#include <LIB_COMPILING.h>

class LIB_API SDLUtility
{
public:

	SDLUtility();
	~SDLUtility();

	SDL_Rect Rect(int x, int y, int w, int h);

	Uint8* Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	//static SDLUtility Rect(int x, int y, int w, int h);

private:


};

