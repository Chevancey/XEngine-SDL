#pragma once

#include <LIB_COMPILING.h>
#include <entt/fwd.hpp> //< header spécial qui fait des déclarations anticipées des classes de la lib

class LIB_API AnimationSystem
{
public:
	AnimationSystem(entt::registry& registry);

	void Update(float deltaTime);

private:
	entt::registry& m_registry;
};