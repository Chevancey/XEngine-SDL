#include"Shape.h"
#include"Vector2.h"

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
