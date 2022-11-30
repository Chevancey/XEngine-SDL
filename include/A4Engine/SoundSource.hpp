#pragma once
#include <AL\al.h>
#include <A4Engine/Export.hpp>
#include "A4Engine/Vector2.hpp"
//#include "Entity.h"

/// Sound Sources enherits from entity class as it needs a position. It's purpose is to assign a sound effect to 3D space.

//class Vector2f;

class A4ENGINE_API SoundSource {
public:
	SoundSource();
	~SoundSource();

	void Play(const ALuint buffer_to_play);
	void Stop();
	void Pause();
	void Resume();

	void NewPlay(const ALuint buffer_to_play);
	void SetLooping(const bool& loop);

	//Spacial Functions
	//glm::vec3 getOrientation();
	//float getGain();

	//void SetAttunation();
	//void SetOrientation();
	//void SetGain();

	bool isPlaying();
	void SetPosition(Vector2f pos);


private:
	ALuint p_Source;
	float p_Pitch = 1.f;
	float p_Gain = 1.f;
	float p_Velocity[3] = { 0,0,0 };
	bool p_LoopSound = false;
	ALuint p_Buffer = 0;
};

