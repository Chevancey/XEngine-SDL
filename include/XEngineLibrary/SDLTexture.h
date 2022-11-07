#pragma once
#include <SDL.h>
#include <string>
#include <LIB_COMPILING.h>

class SDLRenderer;
class SDLSurface;


class LIB_API SDLTexture
{
public:
	SDLTexture(const SDLTexture&) = delete; // constructeur par copie
	SDLTexture(SDLTexture&& texture) noexcept; // constructeur par mouvement
	~SDLTexture();

	const std::string& GetFilePath() const;
	SDL_Texture* get() const;
	SDL_Rect GetRect() const;

	SDLTexture& operator=(const SDLTexture&) = delete; // opérateur d'assignation par copie
	SDLTexture& operator=(SDLTexture&&) noexcept; // opérateur d'assignation par mouvement

	static SDLTexture LoadFromFile(SDLRenderer& renderer, const std::string& filepath);
	static SDLTexture LoadFromSurface(SDLRenderer& renderer, const SDLSurface& surface);

private:
	SDLTexture(SDL_Texture* texture, std::string filepath = "");

	SDL_Texture* m_texture;
	std::string m_filepath;
};

