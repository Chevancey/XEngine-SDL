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

