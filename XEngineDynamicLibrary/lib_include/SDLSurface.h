#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <LIB_COMPILING.h>

class LIB_API SDLSurface
{
public:
	SDLSurface(const SDLSurface&) = delete;
	SDLSurface(SDLSurface&& surface);

	SDLSurface();
	~SDLSurface();
	SDLSurface& operator=(SDLSurface&& surface) noexcept;

	static bool textureExisting(const std::string& filepath);
	SDL_Surface* get();
	static SDLSurface LoadFromFile(const std::string& filepath);

private:
	SDLSurface(SDL_Surface* surface);
	SDL_Surface* m_surface;
};