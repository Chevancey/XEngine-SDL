#include "Sprite.h"
#include "SDLRenderer.h"
#include "SDLTexture.h"
#include "MemoryManagement.h"

Sprite::Sprite(const std::shared_ptr<SDLTexture>& texture) :
	Sprite(texture, texture->GetRect(), 0, 0)
{
}

Sprite::Sprite(const std::shared_ptr<SDLTexture>& texture, const SDL_Rect& rect, int frameIndex, int frameCount) :
	m_texture(texture),
	m_rect(rect),
	m_width(rect.w),
	m_height(rect.h),
	m_frameCount(frameCount),
	m_frameIndex(frameIndex)
{

}

void Sprite::Draw(SDLRenderer& renderer, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = m_width;
	dest.h = m_height;

	renderer.RenderCopy(*m_texture, m_rect, dest);
}

int Sprite::GetHeight() const
{
	return m_height;
}

int Sprite::GetWidth() const
{
	return m_width;
}

void Sprite::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Sprite::SetRect(SDL_Rect rect)
{
	m_rect = rect;
}

void Sprite::Animate(float detlaTime)
{
	m_timer += detlaTime;

	if (m_timer > 0.1f)
	{
		m_timer -= 0.1f;
		m_frameIndex++;

		if (m_frameIndex >= m_frameCount)
		{
			m_frameIndex = 0;
		}

		std::cout << m_width << std::endl;

		m_rect = { m_frameIndex * 64, 0, m_rect.w, m_rect.h };
	}
}