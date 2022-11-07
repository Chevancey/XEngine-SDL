#pragma once

#include <LIB_COMPILING.h>
#include <SDL.h>
#include <string_view>

class SDLTexture;
class SDLWindow;

class LIB_API SDLRenderer
{
public:

	SDLRenderer(SDLWindow& window, std::string_view rendererName = "", Uint32 flags = 0);
	SDLRenderer(const SDLRenderer&) = delete; // constructeur par copie
	SDLRenderer(SDLRenderer&& renderer) noexcept; // constructeur par mouvement
	~SDLRenderer();

	void Clear();
	SDL_Renderer* get() const;
	void Present();
	void RenderCopy(const SDLTexture& texture);
	void RenderCopy(const SDLTexture& texture, const SDL_Rect& dst);
	void RenderCopy(const SDLTexture& texture, const SDL_Rect& src, const SDL_Rect& dst);
	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	SDLRenderer& operator=(const SDLRenderer&) = delete; // opérateur d'assignation par copie
	SDLRenderer& operator=(SDLRenderer&&) noexcept; // opérateur d'assignation par copie

private:
	SDL_Renderer* m_renderer;
};
