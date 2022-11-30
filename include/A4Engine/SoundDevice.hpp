#pragma once

#include <A4Engine/Export.hpp>
#include <AL/alc.h>
#include <AL/al.h>
#include <iostream>
#include <vector>
#include "A4Engine/Vector2.hpp"

//#include "Entity.h"

// This class is for the listener of all sounds in the scene. It enherits from the entity Class as it requires a position and rotation.
// Attenuation is set to key AL_EXPONENT_DISTANCE_CLAMPED as this is universally standard but it can be changed however is needed

class A4ENGINE_API SoundDevice
{
public:

	static SoundDevice* get();
	static void Init();

	// Spacial Functions

	void SetAttunation(int key);
	//void SetOrientation(glm::vec3 at, glm::vec3 up);
	void SetGain(const float& val);
	void SetPosition(Vector2f pos);


private:
	SoundDevice();
	~SoundDevice();


	ALCdevice* p_ALCDevice;
	ALCcontext* p_ALCContext;
};