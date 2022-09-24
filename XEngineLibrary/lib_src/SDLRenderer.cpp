#include "SDLRenderer.h"
#include "SDLWindow.h"
#include "SDLTexture.h"

SDLRenderer::SDLRenderer(SDLWindow& window)
{
	m_renderer = SDL_CreateRenderer(window.get(), 0, 0);
}

SDLRenderer::~SDLRenderer()
{
	SDL_DestroyRenderer(m_renderer);
}

void SDLRenderer::SDLDrawBG(Uint8* color)
{
	//std::cout << std::to_string(color[3]) << std::endl;
	SDL_SetRenderDrawColor(m_renderer, color[0] , color[1], color[2], color[3]);
}

void SDLRenderer::Clear()
{
	SDL_RenderClear(m_renderer);
}

void SDLRenderer::Present()
{
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* SDLRenderer::get()
{
	return m_renderer;
}

void SDLRenderer::RenderCopy(const SDLTexture& texture)
{
	SDL_RenderCopy(m_renderer, texture.get(), nullptr, nullptr);
}

void SDLRenderer::RenderCopy(const SDLTexture& texture, const SDL_Rect& rect)
{
	SDL_RenderCopy(m_renderer, texture.get(), nullptr, &rect);
}

void SDLRenderer::RenderCopy(const SDLTexture& texture, const SDL_Rect& src, const SDL_Rect& rect)
{
	SDL_RenderCopy(m_renderer, texture.get(), &src, &rect);
}