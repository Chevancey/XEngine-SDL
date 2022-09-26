#pragma once
#include<SDL.h>

class SDLTime
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