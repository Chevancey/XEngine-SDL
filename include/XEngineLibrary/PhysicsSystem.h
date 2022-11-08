//#include "chipmunk/chipmunk.h"
//#include "entt/entt.hpp"
//#include "Vector2.h"
//
//// The Body Part
//class RigidBodyComponent
//{
//
//public:
//
//	RigidBodyComponent(entt::entity entity, float mass);
//
//private:
//	cpBody* body;
//};
//
//
//// The Space Part
//class PhsyicsSystem
//{
//
//public:
//	PhsyicsSystem();
//
//	void SetGravity(Vector2f gravity);
//	void SetDamping(float damping);
//
//private:
//	cpSpace* space;
//};
//
////The Shape Part
//class Shape
//{
//public:
//
//	Shape();
//
//	~Shape();
//
//protected:
//	cpShape* shape;
//};
//
////class CircleShape : private Shape
////{
////public:
////	CircleShape(cpBody* body, float radious);
////
////private:
////
////};
////
////class BoxShape : private Shape
////{
////public:
////	BoxShape(cpBody* body, float width, float height);
////private:
////
////};
////
////class SegmentShape : private Shape
////{
////public:
////	SegmentShape(cpBody* body, Vector2f coordOne, Vector2f coordTwo);
////
////private:
////
////};
//
