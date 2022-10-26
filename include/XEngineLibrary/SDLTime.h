#pragma once
#include<SDL.h>
#include <LIB_COMPILING.h>

class LIB_API SDLTime
{
public:
	SDLTime();
	
	~SDLTime();

	void CountDeltaTime();
	
	float getDeltaTime();

private:
	float deltaTime;
	Uint64 lastUpdate;
};