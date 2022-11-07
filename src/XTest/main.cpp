#include <iostream>
#include<vector>
#include<string>

#define DR_WAV_IMPLEMENTATION

#include"DegRad.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "dr_wav.h"

int main() 
{
	//const ALCchar* name = nullptr;

	const ALCchar* deviceList = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
	std::vector<std::string> devices;
	
	while (true) 
	{
		std::size_t length = std::strlen(deviceList);
		if (length == 0)
			break;

		deviceList += length + 1;
	}

	ALCdevice* p_ALCDevice = alcOpenDevice(nullptr);
	if (!p_ALCDevice)
		throw("failed to get sound device");

	ALCcontext* p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);
	if (!p_ALCContext)
		throw("Failed to set sound context");

	alcMakeContextCurrent(p_ALCContext);
	if (!alcMakeContextCurrent(p_ALCContext))
		throw("failed to make context current");

	ALuint buffer;
	alGenBuffers(1, &buffer);

	//std::vector<std::int16_t> samples;
	//float sin = 0;
	//for (std::size_t i = 0; i < 44100 * 100; ++i) 
	//{
	//	sin = std::sin(2 * pi * i / 44100) * 100.f;
	//	samples.push_back(std::sin(float(2 * pi * i / 44100 * sin)) * 32767);
	//	//samples.push_back(std::sin(float(2 * pi * i / 44100 * sin)) * 32767);
	//}

	drwav wav;
	if (!drwav_init_file(&wav, "assets/MaenderAlkoor.wav", nullptr)) 
	{
		std::cout << "Could not open .wav file" << std::endl;
		return 0;
	}

	std::vector<std::int16_t> samples(wav.totalPCMFrameCount * wav.channels);
	drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());

	alBufferData(buffer, (wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, samples.data(), samples.size(), wav.sampleRate);

	drwav_uninit(&wav);

	ALuint source;

	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, AL_TRUE);
	alSourcePlay(source);

	std::getchar();


	// destroy every thing

	alDeleteBuffers(1, &buffer);

	// assign current context to nullptr
	alcMakeContextCurrent(nullptr);
	if (!alcMakeContextCurrent(nullptr))
		throw("failed to set context to nullptr");

	// destroy context
	alcDestroyContext(p_ALCContext);
	if (p_ALCContext)
		throw("failed to unset during close");

	// close used devices
	alcCloseDevice(p_ALCDevice);
	if (!alcCloseDevice(p_ALCDevice))
		throw("failed to close sound device");

}