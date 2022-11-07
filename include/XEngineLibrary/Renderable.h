#pragma once

#include <LIB_COMPILING.h>

class SDLRenderer;
class SDLTexture;
class Transform;

class LIB_API Renderable // interface
{
public:
	// Il est important pour une classe virtuelle de base d'avoir un destructeur virtuel
	virtual ~Renderable() = default;

	virtual void Draw(SDLRenderer& renderer, const Transform& cameraTransform, const Transform& transform) = 0;
};