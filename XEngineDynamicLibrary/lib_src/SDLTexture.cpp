#include <SDL_image.h>
#include "SDLTexture.h"
#include "SDLRenderer.h"
#include "SDLSurface.h"
#include "MemoryManagement.h"


SDLTexture::SDLTexture(SDLTexture&& texture)
{
	m_texture = texture.m_texture;
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

std::string SDLTexture::getName() 
{
	return m_name;
}

SDLTexture SDLTexture::LoadFromFile(SDLRenderer& renderer, const std::string& filepath)
{
	//std::cout << temp << std::endl;
	return LoadFromSurface(renderer, SDLSurface::LoadFromFile(filepath), filepath);
}

SDLTexture SDLTexture::LoadFromSurface(SDLRenderer& renderer, SDLSurface& surface, const std::string& filepath)
{
	MemoryManagement::checkExistance(SDL_CreateTextureFromSurface(renderer.get(), surface.get()),);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface.get());
	return SDLTexture(texture, filename);
}

SDLTexture::SDLTexture(SDL_Texture* texture, const std::string& filepath) :
	m_texture(texture)
{
	m_name = getFileName(filepath);
	std::cout << m_name << std::endl;
}

std::string SDLTexture::getFileName(const std::string& s) 
{
	size_t i = s.rfind('/', s.length());
	return(s.substr(i + 1, s.length() - i));
}