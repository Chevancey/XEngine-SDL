#pragma once

#include <LIB_COMPILING.h>
#include <entt/fwd.hpp> //< header spécial qui fait des déclarations anticipées des classes de la lib

class SDLRenderer;

class LIB_API RenderSystem
{
public:
	RenderSystem(SDLRenderer& renderer, entt::registry& registry);

	void Update(float deltaTime);

private:
	SDLRenderer& m_renderer;
	entt::registry& m_registry;
};