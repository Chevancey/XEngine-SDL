#include "SDLUtility.h"

SDLUtility::SDLUtility()
{
}

SDLUtility::~SDLUtility()
{
}

SDL_Rect SDLUtility::Rect(int x, int y, int w, int h) 
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;

}

Uint8* SDLUtility::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Uint8 color[]
	{
		r, g, b, a
	};

	return color;
}