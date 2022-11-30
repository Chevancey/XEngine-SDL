#pragma once
#include <A4Engine/Export.hpp>
#include <AL/al.h>
#include <sndfile.h>
#include <cstddef>
#include <AL/alext.h>
#include <malloc.h>
#include <iostream>

/// Sound Track class is for creating a sound source which contains 4 buffer to play long pieces of soundtracks suchas music or ambient noise.

class A4ENGINE_API SoundTrack
{
public:
	// giving constructor file name and location.
	SoundTrack(const char* fileName);
	~SoundTrack();

	void UpdateBufferStream();

	void Play();
	void Stop();
	void Pause();
	void Resume();

	bool isPlaying();

	void SetLooping(const bool& loop);

	ALint getSource();

private:
	//source of sound
	ALuint p_Source;
	// sample size of buffer
	static const int BUFFER_SAMPLES = 8192;
	//number of buffers, once one is finished marked as done then goes to next. the sound track will flow through 4 of them.
	static const int NUM_BUFFERS = 4;
	ALuint p_Buffers[NUM_BUFFERS];
	// needed because file is updated 4 times for each buffer
	SNDFILE* p_SndFile;
	//
	SF_INFO p_Sfinfo;
	//pointer tp memory of the soundtrack
	short* p_Membuf;
	// what format is it?
	ALenum p_Format;

	//Only one soundtrack at a time
	SoundTrack() = delete;
};