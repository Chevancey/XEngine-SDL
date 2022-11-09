#include "PhysicsSystem.h"


PhsyicsSystem::PhsyicsSystem(entt::registry& registery)
{
	space = cpSpaceNew();
	
	cpSpaceSetDamping(space, 0.5f);
}

void PhsyicsSystem::SetGravity(Vector2f gravity)
{
	cpSpaceSetGravity(space, { gravity.x, gravity.y });
}

void PhsyicsSystem::SetDamping(float damping)
{
	cpSpaceSetDamping(space, damping);
}


