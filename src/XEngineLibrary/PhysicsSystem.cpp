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


RigidBodyComponent::RigidBodyComponent(entt::entity entity, float mass) 
{
	body = cpBodyNew(mass, cpMomentForBox(mass, 256, 256));
}

Shape::~Shape() 
{

}

CircleShape::CircleShape(cpBody* body, float radious)
{
	shape = cpCircleShapeNew(body, radious, {0.f,0.f});
}

BoxShape::BoxShape(cpBody* body, float width, float height)
{
	shape = cpBoxShapeNew(body, width, height, 0.f);
}

SegmentShape::SegmentShape(cpBody* body, Vector2f coordOne, Vector2f coordTwo)
{
	shape = cpSegmentShapeNew(body, { coordOne.x, coordOne.y }, { coordTwo.x, coordTwo.y }, 0.f);
}

