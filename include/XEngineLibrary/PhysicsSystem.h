#include "chipmunk/chipmunk.h"
#include "entt/entt.hpp"
#include "Vector2.h"

// The Body Part



 //The Space Part
class PhsyicsSystem
{

public:

	PhsyicsSystem(entt::registry& registery);

	void SetGravity(Vector2f gravity);
	void SetDamping(float damping);


private:

	cpSpace* space;

};

//The Shape Part
class Shape
{
public:

	Shape();

	~Shape();

protected:
	cpShape* shape;
};

class CircleShape : private Shape
{
public:
	CircleShape(cpBody* body, float radious);

private:

};

class BoxShape : private Shape
{
public:
	BoxShape(cpBody* body, float width, float height);
private:

};

class SegmentShape : private Shape
{
public:
	SegmentShape(cpBody* body, Vector2f coordOne, Vector2f coordTwo);

private:

};

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

