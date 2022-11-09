#include "RigidBodyComponent.h"
#include "Shape.h"

RigidBodyComponent::RigidBodyComponent(entt::entity entity, float mass) 
{
	body = cpBodyNew(mass, cpMomentForBox(mass, 256, 256));
}
