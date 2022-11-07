#include <SDLRenderer.h>
#include <SDLTexture.h>
#include <SDLWindow.h>
#include <SDL.h>

SDLRenderer::SDLRenderer(SDLWindow& window, std::string_view rendererName, Uint32 flags)
{
	int choosenDriver = -1;

	int numDrivers = SDL_GetNumRenderDrivers();
	for (int i = 0; i < numDrivers; ++i)
	{
		SDL_RendererInfo info;
		SDL_GetRenderDriverInfo(i, &info);

		if (info.name == rendererName)
			choosenDriver = i;
	}

	m_renderer = SDL_CreateRenderer(window.get(), choosenDriver, flags);
}

SDLRenderer::SDLRenderer(SDLRenderer&& renderer) noexcept
{
	m_renderer = renderer.m_renderer;
	renderer.m_renderer = nullptr;
}

SDLRenderer::~SDLRenderer()
{
	SDL_DestroyRenderer(m_renderer);
}

void SDLRenderer::Clear()
{
	SDL_RenderClear(m_renderer);
}

SDL_Renderer* SDLRenderer::get() const
{
	return m_renderer;
}

void SDLRenderer::Present()
{
	SDL_RenderPresent(m_renderer);
}

void SDLRenderer::RenderCopy(const SDLTexture& texture)
{
	SDL_RenderCopy(m_renderer, texture.get(), nullptr, nullptr);
}

void SDLRenderer::RenderCopy(const SDLTexture& texture, const SDL_Rect& dst)
{
	SDL_RenderCopy(m_renderer, texture.get(), nullptr, &dst);
}

void SDLRenderer::RenderCopy(const SDLTexture& texture, const SDL_Rect& src, const SDL_Rect& dst)
{
	SDL_RenderCopy(m_renderer, texture.get(), &src, &dst);
}

void SDLRenderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

SDLRenderer& SDLRenderer::operator=(SDLRenderer&& renderer) noexcept
{
	std::swap(m_renderer, renderer.m_renderer);
	return *this;
}