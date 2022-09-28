#pragma once
#include <SDL.h>
#include <string>
#include <LIB_COMPILING.h>

class LIB_API SDLRenderer;
class LIB_API SDLSurface;


class LIB_API SDLTexture
{
public:
	SDLTexture(const SDLTexture&) = delete; // constructeur par copie
	SDLTexture& operator =(const SDLTexture&) = delete; // affectation par copie
	~SDLTexture();

	SDLTexture(SDLTexture&& texture) noexcept; 
	SDLTexture& operator=(SDLTexture&& texture) noexcept;

	SDL_Texture* get() const;
	SDL_Rect GetRect() const;

	static SDLTexture LoadFromFile(SDLRenderer& renderer, const std::string& filepath);
	static SDLTexture LoadFromSurface(SDLRenderer& renderer, SDLSurface& surface);
	static SDLTexture LoadSurface(SDLRenderer& renderer, SDL_Surface* surface);
private:

	SDLTexture(SDL_Texture* texture);
	SDLTexture(SDL_Texture* texture, const std::string& filepath);

	SDL_Texture* m_texture;
};