
#include <SDLTexture.h>
#include <SDLRenderer.h>
#include <SDLSurface.h>
#include <SDL.h>
#include <SDL_image.h>

SDLTexture::SDLTexture(SDLTexture && texture) noexcept :
	m_filepath(std::move(texture.m_filepath))
{
	m_texture = texture.m_texture;
	texture.m_texture = nullptr;
}

SDLTexture::~SDLTexture()
{
	if (m_texture)
		SDL_DestroyTexture(m_texture);
}

const std::string& SDLTexture::GetFilePath() const
{
	return m_filepath;
}

SDL_Texture* SDLTexture::get() const
{
	return m_texture;
}

SDL_Rect SDLTexture::GetRect() const
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &rect.w, &rect.h);

	return rect;
}

SDLTexture& SDLTexture::operator=(SDLTexture&& texture) noexcept
{
	// Les classes peuvent être move directement
	m_filepath = std::move(texture.m_filepath);

	// On possède déjà potentiellement une texture
	// On la donne à texture (qui va être détruit de toute façon)
	// tout en volant son pointeur : on échange donc les pointeurs
	// => std::swap
	std::swap(m_texture, texture.m_texture);
	return *this;
}

SDLTexture SDLTexture::LoadFromFile(SDLRenderer& renderer, const std::string& filepath)
{
	return LoadFromSurface(renderer, SDLSurface::LoadFromFile(filepath));
}

SDLTexture SDLTexture::LoadFromSurface(SDLRenderer& renderer, const SDLSurface& surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface.get());
	return SDLTexture(texture, surface.GetFilePath());
}

SDLTexture::SDLTexture(SDL_Texture* texture, std::string filepath) :
	m_texture(texture),
	m_filepath(std::move(filepath))
{
}
