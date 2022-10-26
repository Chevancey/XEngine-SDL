#pragma once

#include <SDL.h>
#include <memory>
#include <LIB_COMPILING.h>

class SDLRenderer;
class SDLTexture;
class Transform;

class LIB_API Sprite
{
public:
	Sprite(std::shared_ptr<const SDLTexture> texture);
	Sprite(std::shared_ptr<const SDLTexture> texture, const SDL_Rect& rect);

	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	~Sprite() = default;

	void Draw(SDLRenderer& renderer, const Transform& transform);
	void Resize(int w, int h);

	int GetWidth() const;
	int GetHeight() const;

	void SetRect(SDL_Rect rect);
	void Animate(float detlaTime);

	Sprite& operator=(const Sprite&) = delete;
	Sprite& operator=(Sprite&&) = default;

private:

	std::shared_ptr<const SDLTexture> m_texture;
	SDL_Rect m_rect;
	int m_width;
	int m_height;
};
