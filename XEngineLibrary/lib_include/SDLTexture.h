#pragma once
#include <SDL.h>
#include <string>

class SDLRenderer;
class SDLSurface;


class SDLTexture
{
public:
	SDLTexture(const SDLTexture&) = delete; // constructeur par copie
	SDLTexture(SDLTexture&& texture); // constructeur par mouvement
	~SDLTexture();

	SDL_Texture* get() const;
	SDL_Rect GetRect() const;

	//void SetRect(int ) const;

	SDLTexture& operator=(SDLTexture&& texture) noexcept; // opérateur d'assignation par copie
	//SDLTexture& operator=(SDLTexture&&); // opérateur d'assignation par mouvement

	//static SDLTexture LoadFromFile(SDLRenderer& renderer, const std::string& filepath);
	static SDLTexture LoadFromFile(SDLRenderer& renderer, const std::string& filepath);
	//static SDLTexture LoadFromSurface(SDLRenderer& renderer, SDLSurface& surface, const std::string& name);
	static SDLTexture LoadFromSurface(SDLRenderer& renderer, SDLSurface& surface, const std::string& filename);


private:
	std::string getFileName(const std::string& s);
	SDLTexture(SDL_Texture* texture, const std::string& filename);
	//SDLTexture(SDL_Texture* texture, const std::string& filename);

	std::string m_name;

	SDL_Texture* m_texture;
};