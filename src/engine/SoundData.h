#pragma once

#include <string>
#include <vector>

#include "AL/al.h"
#include "AudioFile.h"

// This class is used to store raw sound data. It must be given to one of the SoundManager static functions to be played.
class SoundData {
public:

	// start and end are measured in seconds
	SoundData(const std::string& filepath, float start = -1.0f, float end = -1.0f);

	// must provide pcm audio data
	SoundData(const std::vector<uint16_t>& rawData, int frequency, int bitsPerSample, int channels);

	SoundData(SoundData& sound);

	~SoundData();


public:
	// start and end are measured in seconds
	SoundData getSubset(float start, float end);

	std::vector<unsigned char>& getRawData();
	int getFrequency();
	int getBitsPerSample();
	int getChannels();

	float getDuration();

	ALuint getBufferID();

	void saveToFile(const std::string& filepath);

private:
	bool loadWave(const std::string& filepath, ALenum& format, ALsizei& freq, ALsizei& size);
	std::string getALerrorString(ALenum errorCode);

private:
	std::vector<unsigned char> rawData;
	int frequency;
	int bitsPerSample;
	int channels;

	ALuint bufferID;

};