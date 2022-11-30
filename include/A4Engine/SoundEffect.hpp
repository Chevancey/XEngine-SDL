#pragma once
#include <A4Engine/Export.hpp>
#include <AL\al.h>
#include <vector>

/// Sound effect class is used to load sound effects into the game. It is set to be a singleton as this class is stored in a uint32_t.

class A4ENGINE_API SoundEffect
{
public:
	static SoundEffect* get();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);

private:
	SoundEffect();
	~SoundEffect();

	std::vector<ALuint> p_SoundEffectBuffers;
};
