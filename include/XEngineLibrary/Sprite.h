#pragma once

#include <LIB_COMPILING.h>
#include <Renderable.h>
#include <Vector2.h>
#include <SDL.h>
#include <memory>

class SDLRenderer;
class SDLTexture;
class Transform;

class LIB_API Sprite : public Renderable // Une portion d'une texture
{
public:
	Sprite(std::shared_ptr<const SDLTexture> texture);
	Sprite(std::shared_ptr<const SDLTexture> texture, const SDL_Rect& rect);
	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	~Sprite() = default;

	void Draw(SDLRenderer& renderer, const Transform& cameraTransform, const Transform& transform) override;

	int GetHeight() const;
	const Vector2f& GetOrigin() const;
	int GetWidth() const;

	void Resize(int width, int height);

	void SetOrigin(const Vector2f& origin);
	void SetRect(SDL_Rect rect);

	Sprite& operator=(const Sprite&) = default;
	Sprite& operator=(Sprite&&) = default;

private:
	std::shared_ptr<const SDLTexture> m_texture;
	SDL_Rect m_rect;
	Vector2f m_origin;
	int m_width;
	int m_height;
};
