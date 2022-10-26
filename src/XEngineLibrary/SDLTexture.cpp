#include <SDL_image.h>
#include "SDLTexture.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"

SDLTexture::SDLTexture(SDLTexture&& texture) noexcept :
	m_texture(texture.m_texture)
{
	texture.m_texture = nullptr;
}

SDLTexture::~SDLTexture()
{
	if (m_texture)
		SDL_DestroyTexture(m_texture);
}

SDL_Texture* SDLTexture::get() const
{
	return m_texture;
}

SDLTexture& SDLTexture::operator=(SDLTexture&& texture) noexcept 
{
	std::swap(m_texture, texture.m_texture);
	
	return *this;
}

SDL_Rect SDLTexture::GetRect() const
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &rect.w, &rect.h);

	return rect;
}

SDLTexture SDLTexture::LoadFromFile(SDLRenderer& renderer, const std::string& filepath)
{
	return LoadFromSurface(renderer, SDLSurface::LoadFromFile(filepath));
}

SDLTexture SDLTexture::LoadFromSurface(SDLRenderer& renderer, SDLSurface& surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface.get());
	return SDLTexture(texture);
}

SDLTexture SDLTexture::LoadSurface(SDLRenderer& renderer, SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
	return SDLTexture(texture);
}

SDLTexture::SDLTexture(SDL_Texture* texture):
	m_texture(texture)
{
}