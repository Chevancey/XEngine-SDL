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
	SDLTexture(SDLTexture&& texture); // constructeur par mouvement
	~SDLTexture();

	SDL_Texture* get() const;
	std::string getName();
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