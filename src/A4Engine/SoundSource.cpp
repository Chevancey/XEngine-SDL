#include "A4Engine/SoundSource.hpp"
#include <iostream>

SoundSource::SoundSource()
{
	alGenSources(1, &p_Source);
	alSourcef(p_Source, AL_PITCH, p_Pitch);
	alSourcef(p_Source, AL_GAIN, p_Gain);
	//position in scene
	alSource3f(p_Source, AL_POSITION, 0, 0, 0);
	alSource3f(p_Source, AL_VELOCITY, p_Velocity[0], p_Velocity[1], p_Velocity[2]);
	alSourcei(p_Source, AL_LOOPING, p_LoopSound);
	alSourcei(p_Source, AL_BUFFER, p_Buffer);
}

SoundSource::~SoundSource()
{
	alDeleteSources(1, &p_Source);
}

void SoundSource::Play(const ALuint buffer_to_play)
{
	if (buffer_to_play != p_Buffer)
	{
		p_Buffer = buffer_to_play;
		alSourcei(p_Source, AL_BUFFER, (ALint)p_Buffer);
	}

	alSourcePlay(p_Source);
}

void SoundSource::Stop() 
{
	alSourceStop(p_Source);
}

void SoundSource::Pause() 
{
	alSourcePause(p_Source);
}

void SoundSource::Resume() 
{
	alSourcePlay(p_Source);
}

void SoundSource::NewPlay(const ALuint buffer_to_play)
{
	// replacing buffer to play new sound
	if (buffer_to_play != p_Buffer)
	{
		p_Buffer = buffer_to_play;
		alSourcei(p_Source, AL_BUFFER, (ALint)p_Buffer);
	}
}

void SoundSource::SetLooping(const bool& loop) 
{
	// giving instruction to loop sound effect
	alSourcei(p_Source, AL_LOOPING, (ALint)loop);
}

bool SoundSource::isPlaying() 
{
	//ALint for return in bool
	ALint playState;
	// query: is it playing?
	alGetSourcei(p_Source, AL_SOURCE_STATE, &playState);
	// value is Playing
	return (playState == AL_PLAYING);
}

void SoundSource::SetPosition(Vector2f pos)
{
	alSource3f(p_Source, AL_POSITION, pos.x, pos.y, 0);
}

//float SoundSource::p_Position[3]()
//{ 
//	return position.x, position.y, position.z;
//}