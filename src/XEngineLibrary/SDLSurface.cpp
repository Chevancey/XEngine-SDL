#include <SDLSurface.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <memory>
#include <iostream>

SDLSurface::SDLSurface(int width, int height)
{
	m_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
}

SDLSurface::SDLSurface(SDLSurface&& surface) noexcept :
	m_filepath(std::move(surface.m_filepath))
{
	m_surface = surface.m_surface;
	surface.m_surface = nullptr;
}

SDLSurface::~SDLSurface()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

void SDLSurface::FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	assert(m_surface);
	SDL_FillRect(m_surface, &rect, SDL_MapRGBA(m_surface->format, r, g, b, a));
}

const std::string& SDLSurface::GetFilePath() const
{
	return m_filepath;
}

SDL_Surface* SDLSurface::get() const
{
	return m_surface;
}

Uint8* SDLSurface::GetPixels()
{
	return static_cast<Uint8*>(m_surface->pixels);
}

const Uint8* SDLSurface::GetPixels() const
{
	return static_cast<const Uint8*>(m_surface->pixels);
}

bool SDLSurface::IsValid() const
{
	return m_surface != nullptr;
}

SDLSurface& SDLSurface::operator=(SDLSurface&& surface) noexcept
{
	// Les classes peuvent être move directement
	m_filepath = std::move(surface.m_filepath);

	// On possède déjà potentiellement une Surface
	// On la donne à Surface (qui va être détruit de toute façon)
	// tout en volant son pointeur : on échange donc les pointeurs
	// => std::swap
	std::swap(m_surface, surface.m_surface);
	return *this;
}

SDLSurface SDLSurface::LoadFromFile(std::string filepath)
{
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (!surface)
		std::cerr << IMG_GetError() << std::endl;

	return SDLSurface(surface, std::move(filepath));
}

SDLSurface::SDLSurface(SDL_Surface* surface, std::string filepath) :
	m_surface(surface),
	m_filepath(std::move(filepath))
{
}


