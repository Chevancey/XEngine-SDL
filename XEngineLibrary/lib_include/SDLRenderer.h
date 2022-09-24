#pragma once
#include <iostream>
#include <SDL.h>

class SDLWindow;
class SDLRednering;
class SDLTexture;

class SDLRenderer
{
public:
	
	SDLRenderer(SDLWindow& window);
	SDLRenderer(const SDLRenderer&) = delete;
	//SDLRenderer(const SDLRenderer&) noexcept;

	~SDLRenderer();

	void SDLDrawBG(Uint8 * color);
	void Clear();
	void Present();

	void RenderCopy(const SDLTexture& texture);
	void RenderCopy(const SDLTexture& texture, const SDL_Rect& rect);
	void RenderCopy(const SDLTexture& texture, const SDL_Rect& src, const SDL_Rect& rect);

	SDL_Renderer* get();

	SDLRenderer& operator = (const SDLWindow&) = delete;
private:
	SDL_Renderer* m_renderer;
};