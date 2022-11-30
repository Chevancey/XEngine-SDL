#include"A4Engine/SoundTrack.hpp"

SoundTrack::SoundTrack(const char* fileName)
{
	alGenSources(1, &p_Source);
	alGenBuffers(NUM_BUFFERS, p_Buffers);
	std::size_t frame_size;

	p_SndFile = sf_open(fileName, SFM_READ, &p_Sfinfo);
	if (!p_SndFile)
	{
		throw("Could not open sound track: check path");
	}

	if (p_Sfinfo.channels == 1)
		p_Format = AL_FORMAT_MONO16;
	else if (p_Sfinfo.channels == 2)
		p_Format = AL_FORMAT_STEREO16;
	else if (p_Sfinfo.channels == 3)
	{
		if (sf_command(p_SndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			p_Format = AL_FORMAT_BFORMAT2D_16;
	}
	else if (p_Sfinfo.channels == 4)
	{
		if (sf_command(p_SndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			p_Format = AL_FORMAT_BFORMAT3D_16;
	}
	if (!p_Format)
	{
		sf_close(p_SndFile);
		p_SndFile = NULL;
		throw("Unsupported channel count from file");
	}

	frame_size = ((size_t)BUFFER_SAMPLES * (size_t)p_Sfinfo.channels) * sizeof(short);
	p_Membuf = static_cast<short*>(malloc(frame_size));
}

SoundTrack::~SoundTrack()
{
	// delete source
	alDeleteSources(1, &p_Source);

	//close file
	if (p_SndFile)
		sf_close(p_SndFile);

	// set file to nullptr for error avoidance
	p_SndFile = nullptr;

	// freeing the buffer memory
	free(p_Membuf);

	// removing all buffers
	alDeleteBuffers(NUM_BUFFERS, p_Buffers);

}

void SoundTrack::UpdateBufferStream()
{
	ALint processed, state;

	// clear error 
	alGetError();
	// information on source for buffer
	alGetSourcei(p_Source, AL_SOURCE_STATE, &state);
	alGetSourcei(p_Source, AL_BUFFERS_PROCESSED, &processed);
	if (alGetError() != AL_NO_ERROR)
	{
		throw("error checking music source state");
	}

	/* Unqueue and handle each processed buffer */
	while (processed > 0)
	{
		ALuint bufid;
		sf_count_t slen;

		alSourceUnqueueBuffers(p_Source, 1, &bufid);
		processed--;

		/* Read the next chunk of data, refill the buffer, and queue it
		 * back on the source */
		slen = sf_readf_short(p_SndFile, p_Membuf, BUFFER_SAMPLES);
		
		if (slen > 0)
		{
			slen *= p_Sfinfo.channels * (sf_count_t)sizeof(short);
			alBufferData(bufid, p_Format, p_Membuf, (ALsizei)slen, p_Sfinfo.samplerate);
			alSourceQueueBuffers(p_Source, 1, &bufid);
		}

		if (alGetError() != AL_NO_ERROR)
		{
			throw("error buffering music data");
		}
	}

	/* Make sure the source hasn't underrun */
	if (state != AL_PLAYING && state != AL_PAUSED)
	{
		ALint queued;
		alSourcePlay(p_Source);
		/* If no buffers are queued, playback is finished */
		alGetSourcei(p_Source, AL_BUFFERS_QUEUED, &queued);
		//std::cout << queued << std::endl;

		if (queued == 0)
			return;

		alSourcePlay(p_Source);
		if (alGetError() != AL_NO_ERROR)
		{
			throw("error restarting music playback");
		}
	}
}

void SoundTrack::Play()
{
	ALsizei i;

	//incase of any AL errors
	alGetError();

	// goes back to 0.0
	alSourceRewind(p_Source);
	//clear buffer
	alSourcei(p_Source, AL_BUFFER, 0);
	
	// Filling all 4 buffers with data
	for (i = 0; i < NUM_BUFFERS; i++)
	{
		//collecting data for each buffers
		sf_count_t slen = sf_readf_short(p_SndFile, p_Membuf, BUFFER_SAMPLES);
		if (slen < 1) break;

		slen *= p_Sfinfo.channels * (sf_count_t)sizeof(short);
		alBufferData(p_Buffers[i], p_Format, p_Membuf, (ALsizei)slen, p_Sfinfo.samplerate);
	}

	// check for errors
	if (alGetError() != AL_NO_ERROR)
	{
		throw("Error buffering for playback");
	}

	// queue and play
	alSourceQueueBuffers(p_Source, i, p_Buffers);
	alSourcePlay(p_Source);
	// check for errors on playback
	if (alGetError() != AL_NO_ERROR)
	{
		throw("Error starting playback");
	}
}


void SoundTrack::Stop()
{
	alSourceStop(p_Source);
}

void SoundTrack::Pause()
{
	alSourcePause(p_Source);
}

void SoundTrack::Resume()
{
	alSourcePlay(p_Source);
}

bool SoundTrack::isPlaying()
{
	//ALint for return in bool
	ALint playState;
	// query: is it playing?
	alGetSourcei(p_Source, AL_SOURCE_STATE, &playState);
	// value is Playing
	return (playState == AL_PLAYING);
}

void SoundTrack::SetLooping(const bool& loop)
{
	// giving instruction to loop music
	alSourcei(p_Source, AL_LOOPING, (ALint)loop);
}

ALint SoundTrack::getSource()
{
	return p_Source;
}

