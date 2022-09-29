#include "SDLSurface.h"
//#include <SDL_image.h>

SDLSurface::SDLSurface(SDLSurface&& texture)
{
	m_surface = texture.m_surface;
	texture.m_surface = nullptr;
}

SDLSurface::~SDLSurface()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

SDLSurface SDLSurface::LoadFromFile(const std::string& filepath)
{
	//SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (!IMG_Load(filepath.c_str()))
	{
		std::cout << IMG_GetError() << std::endl;
	}

	return SDLSurface(IMG_Load(filepath.c_str()));
}

bool SDLSurface::textureExisting(const std::string& filepath)
{
	if (!IMG_Load(filepath.c_str()))
	{
		return false;
	}

	return true;
}

SDL_Surface* SDLSurface::get()
{
	return m_surface;
}

SDLSurface& SDLSurface::operator=(SDLSurface&& surface) noexcept
{
	std::swap(m_surface, surface.m_surface);

	return *this;
}

SDLSurface::SDLSurface(SDL_Surface* texture) :
	m_surface(texture)
{
}



