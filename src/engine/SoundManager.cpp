#include "SoundManager.h"

#include <array>
#include "AL/al.h"
#include "AL/alc.h"

std::list<int> SoundManager::activeSounds;
std::list<int> SoundManager::activeLoopingSounds;

ALCdevice* SoundManager::device = nullptr;
ALCcontext* SoundManager::context = nullptr;


void SoundManager::__init() {
	device = alcOpenDevice(NULL);

	if (device) {
		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);
	}

	//alEnable(AL_DOPPLER_FACTOR);
	//alDopplerFactor(1.0f);

	//alEnable(AL_SPEED_OF_SOUND);
	//alSpeedOfSound(343.3f);

	//alEnable(AL_DISTANCE_MODEL);
	//alDistanceModel(AL_INVERSE_DISTANCE); // many options
}

void SoundManager::__update() {

	// deletes sources that are no longer playing
	for (std::list<int>::iterator itt = activeSounds.begin(); itt != activeSounds.end(); itt++) {
		ALint val;
		alGetSourcei(*itt, AL_SOURCE_STATE, &val);

		if (val == AL_STOPPED) {
			ALuint id = (ALuint) *itt;
			alDeleteSources(1, &id);
			itt = activeSounds.erase(itt);
		}
	}
}

void SoundManager::__cleanup() {
	context = alcGetCurrentContext();
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

int SoundManager::playAudio(SoundData* sound, float gain, float pitch, bool is3D, std::array<float, 3> position, std::array<float, 3> direction, std::array<float, 3> velocity)
{
	ALuint mySource;
	ALenum err;

	alGetError();
	alGenSources(1, &mySource);
	if ((err = alGetError()) != AL_NO_ERROR) {
		printf("error generating sources : %s\n", getALerrorString(err));
		return -1;
	}

	std::array<ALuint, 1> playList = { sound->getBufferID() };

	// mySource is a speaker. Queue buffers will queue buffers to be played through it
	// alSourcei will only attach a singe buffer at a time. No overlapping.
	alSourceQueueBuffers(mySource, 1, &playList[0]);
	//alSourcei(mySource, AL_BUFFER, myBuffer);
	// alSourceUnqueueBuffers can be used to remove buffers that have already been played.
	// all buffers queued to a source should have the same audio format

	alGetError();

	alSourcePlay(mySource);
	alSourcef(mySource, AL_PITCH, pitch); // this function and a few similar ones can change a large number of parameters about the sound
	alSourcef(mySource, AL_GAIN, gain); // volume

	alSource3f(mySource, AL_POSITION, position[0], position[1], position[2]);
	alSource3f(mySource, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
	alSource3f(mySource, AL_DIRECTION, direction[0], direction[1], direction[2]);

	alSourcei(mySource, AL_SOURCE_RELATIVE, AL_FALSE); // relitive to listener

	return mySource;
}

int SoundManager::loopAudio(SoundData* sound, float gain, float pitch, bool is3D, std::array<float, 3> position, std::array<float, 3> direction, std::array<float, 3> velocity)
{
	ALuint mySource;
	ALenum err;

	alGetError();
	alGenSources(1, &mySource);
	if ((err = alGetError()) != AL_NO_ERROR) {
		printf("error generating sources : %s\n", getALerrorString(err));
		return -1;
	}

	std::array<ALuint, 1> playList = { sound->getBufferID() };

	// mySource is a speaker. Queue buffers will queue buffers to be played through it
	// alSourcei will only attach a singe buffer at a time. No overlapping.
	alSourceQueueBuffers(mySource, 1, &playList[0]);
	//alSourcei(mySource, AL_BUFFER, myBuffer);
	// alSourceUnqueueBuffers can be used to remove buffers that have already been played.
	// all buffers queued to a source should have the same audio format

	alGetError();

	alSourcePlay(mySource);
	alSourcef(mySource, AL_PITCH, pitch); // this function and a few similar ones can change a large number of parameters about the sound
	alSourcef(mySource, AL_GAIN, gain); // volume

	alSource3f(mySource, AL_POSITION, position[0], position[1], position[2]);
	alSource3f(mySource, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
	alSource3f(mySource, AL_DIRECTION, direction[0], direction[1], direction[2]);

	alSourcei(mySource, AL_SOURCE_RELATIVE, AL_TRUE); // relitive to listener

	alSourcei(mySource, AL_LOOPING, AL_TRUE);

	return mySource;

}

void SoundManager::endAllSounds()
{
	// deletes all sources
	for (std::list<int>::iterator itt = activeSounds.begin(); itt != activeSounds.end(); itt++) {
		
		ALuint id = (ALuint)*itt;
		alDeleteSources(1, &id);
		itt = activeSounds.erase(itt);
		
	}
}

void SoundManager::setPitch(int id, float pitch)
{
	alSourcef(id, AL_PITCH, pitch);
}

void SoundManager::setGain(int id, float gain)
{
	alSourcef(id, AL_GAIN, gain);
}

void SoundManager::setPosition(int id, std::array<float, 3> position)
{
	alSource3f(id, AL_POSITION, position[0], position[1], position[2]);
}

void SoundManager::setDirection(int id, std::array<float, 3> direction)
{
	alSource3f(id, AL_DIRECTION, direction[0], direction[1], direction[2]);
}

void SoundManager::setVelocity(int id, std::array<float, 3> velocity)
{
	alSource3f(id, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
}

void SoundManager::pauseSound(int id)
{
	alSourcePause(id);
}

void SoundManager::resumeSound(int id)
{
	alSourcePlay(id);
}

void SoundManager::endSound(int id)
{
	alSourceStop(id);
}

void SoundManager::setListenerGain(float gain)
{
	alListenerf(AL_GAIN, gain);
}

void SoundManager::setListenerPitch(float pitch)
{
	alListenerf(AL_PITCH, pitch);
}

void SoundManager::setListenerPosition(std::array<float, 3> position)
{
	alListener3f(AL_POSITION, position[0], position[1], position[2]);
}

void SoundManager::setListenerDirection(std::array<float, 3> direction)
{
	alListener3f(AL_DIRECTION, direction[0], direction[1], direction[2]);
}

void SoundManager::setListenerVelocity(std::array<float, 3> velocity)
{
	alListener3f(AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
}



std::string SoundManager::getALerrorString(ALenum errorCode) {
	switch (errorCode) {
	case AL_INVALID_NAME:
		return "Invalid name/id";
	case AL_INVALID_ENUM:
		return "Invalid enum";
	case AL_INVALID_VALUE:
		return "Invalid value";
	case AL_INVALID_OPERATION:
		return "Invalid operation";
	case AL_OUT_OF_MEMORY:
		return "Out of memory";
	}
	return "No Error";
}