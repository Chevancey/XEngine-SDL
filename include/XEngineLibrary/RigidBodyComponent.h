#pragma once

#include <chipmunk/chipmunk.h>
#include <entt/entt.hpp>

#include <vector>

class Shape;

class RigidBodyComponent
{

public:
	RigidBodyComponent(float mass);
	RigidBodyComponent(const RigidBodyComponent&) = default;
	RigidBodyComponent(RigidBodyComponent&&) = default;
	RigidBodyComponent& operator=(const RigidBodyComponent&) = default;
	RigidBodyComponent& operator=(RigidBodyComponent&&) = default;
	virtual ~RigidBodyComponent();


	RigidBodyComponent(entt::entity entity, float mass);

	void AddShape();
	void RemoveShape();

private:

	cpBody* body;
	std::vector<Shape*> _shapes;
};