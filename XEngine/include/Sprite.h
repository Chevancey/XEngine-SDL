#pragma once

#include <SDL.h>
#include <memory>

class SDLRenderer;
class SDLTexture;

class Sprite // Une portion d'une texture
{
public:
	Sprite(const std::shared_ptr<SDLTexture>& texture);
	Sprite(const std::shared_ptr<SDLTexture>& texture, const SDL_Rect& rect, int frameIndex, int frameCount);
	
	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;

	~Sprite() = default;

	void Draw(SDLRenderer& renderer, int x, int y);
	void Resize(int w, int h);

	int GetWidth() const;
	int GetHeight() const;

	void SetRect(SDL_Rect rect);
	void Animate(float detlaTime);

	Sprite& operator=(const Sprite&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	//void SetRect(, int w, int h) const;

private:

	const std::shared_ptr<SDLTexture> m_texture;

	SDL_Rect m_rect;
	int m_width;
	int m_height;
	float m_timer;
	int m_frameIndex;
	int m_frameCount;
	//SDL_Rect m_size;
};
