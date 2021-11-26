#pragma once

#include "SoundData.h"

#include <vector>
#include <list>
#include <array>

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

class SoundManager {
public:
	static int playAudio(SoundData* sound, float gain = 1.0f, float pitch = 1.0f, bool is3D = false, std::array<float, 3> position = { 0, 0, 0 }, std::array<float, 3> direction = { 1, 0, 0 }, std::array<float, 3> velocity = { 0, 0, 0 });
	//int playAudio(StreamedSound sound*, volume);

	// looping audio must be manually ended, otherwise it will loop forever.
	static int loopAudio(SoundData* sound, float gain, float pitch, bool is3D = false, std::array<float, 3> position = { 0, 0, 0 }, std::array<float, 3> direction = { 0, 0, 0 }, std::array<float, 3> velocity = { 0, 0, 0 });
	//int loopAudio(StreamedSound* sound, volume);

	static void endAllSounds();

	// decreasing pitch makes it deeper and slower
	static void setPitch(int id, float pitch);

	// gain refers to the volume or loudness
	static void setGain(int id, float gain);

	static void setPosition(int id, std::array<float, 3> position);
	static void setDirection(int id, std::array<float, 3> direction);
	static void setVelocity(int id, std::array<float, 3> velocity);
	
	static void pauseSound(int id);
	static void resumeSound(int id);
	static void endSound(int id);

	static void setListenerGain(float gain);
	static void setListenerPitch(float pitch);
	static void setListenerPosition(std::array<float, 3> position);
	static void setListenerDirection(std::array<float, 3> position);
	static void setListenerVelocity(std::array<float, 3> position);

	static void __init();
	static void __update();
	static void __cleanup();

private:
	static std::list<int> activeSounds;
	static std::list<int> activeLoopingSounds;

	static std::string getALerrorString(ALenum errorCode);

	static ALCdevice* device;
	static ALCcontext* context;

};