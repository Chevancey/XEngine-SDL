#include "A4Engine/SoundDevice.hpp"

#include <stdexcept>


static SoundDevice* _instance = nullptr;

SoundDevice* SoundDevice::get()
{
	Init();
	return _instance;
}

void SoundDevice::Init()
{
	if (_instance == nullptr)
	{
		_instance = new SoundDevice();
	}
}

SoundDevice::SoundDevice()
{
	// nullptr = get default device
	p_ALCDevice = alcOpenDevice(nullptr);
	if (!p_ALCDevice)
		throw("failed to get sound device");

	// create context
	p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);
	if (!p_ALCContext)
		throw("Failed to set sound context");

	// make context current
	if (!alcMakeContextCurrent(p_ALCContext))
		throw("failed to make context current");

	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
		name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
	printf("Opened \"%s\"\n", name);
}

SoundDevice::~SoundDevice()
{
	if (!alcMakeContextCurrent(nullptr))
		throw("failed to set context to nullptr");

	alcDestroyContext(p_ALCContext);
	if (p_ALCContext)
		throw("failed to unset during close");

	if (!alcCloseDevice(p_ALCDevice))
		throw("failed to close sound device");
}

void SoundDevice::SetGain(const float& val)
{
	// clamp between 0 and 5
	float newVol = val;
	if (newVol < 0.f)
		newVol = 0.f;
	else if (newVol > 5.f)
		newVol = 5.f;

	alListenerf(AL_GAIN, newVol);
	alGetError();
}

void SoundDevice::SetAttunation(int key)
{
	if (key < 0xD001 || key > 0xD006)
		throw("bad attunation key");

	alDistanceModel(key);
	alGetError();
}

void SoundDevice::SetPosition(Vector2f pos)
{
	alListener3f(AL_POSITION, pos.x, pos.y, 0);
}

//void SoundDevice::SetOrientation(glm::vec3 at, glm::vec3 up)
//{
//	std::vector<float> ori;
//	ori.push_back(at.x);
//	ori.push_back(at.y);
//	ori.push_back(at.z);
//	ori.push_back(up.x);
//	ori.push_back(up.y);
//	ori.push_back(up.z);
//	alListenerfv(AL_ORIENTATION, ori.data());
//}