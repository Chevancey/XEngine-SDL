#include "chipmunk/chipmunk.h"
#include "entt/entt.hpp"

class Vector2f;

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