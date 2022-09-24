#include "SDLTime.h"

SDLTime::SDLTime() 
{
	lastUpdate = SDL_GetPerformanceCounter();
}

SDLTime::~SDLTime() 
{

}

void SDLTime::CountDeltaTime()
{
	Uint64 now = SDL_GetPerformanceCounter();
	deltaTime = (float)(now - lastUpdate) / SDL_GetPerformanceFrequency();
	lastUpdate = now;
}

float SDLTime::getDeltaTime() 
{
	return deltaTime;
}