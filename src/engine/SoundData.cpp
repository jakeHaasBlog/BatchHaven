#include "SoundData.h"

SoundData::SoundData(const std::string& filepath, float start, float end)
{
	ALenum err;

	alGetError();
	alGenBuffers(1, &bufferID);

	if ((err = alGetError()) != AL_NO_ERROR)
	{
		printf("ERROR: alGenBuffers : %s\n\tIn SoundData(id = %d) filepath constructor\n", getALerrorString(err), bufferID);
		return;
	}

	ALenum format;
	ALsizei size;
	ALsizei freq;

	if (!loadWave(filepath.c_str(), format, freq, size)) {
		printf("SoundData: Error loading audio file: %s\n", filepath.c_str());
		return;
	}

	if (format == AL_FORMAT_MONO8) {
		this->channels = 1;
		this->bitsPerSample = 8;
	}
	if (format == AL_FORMAT_MONO16) {
		this->channels = 1;
		this->bitsPerSample = 16;
	}
	if (format == AL_FORMAT_STEREO8) {
		this->channels = 2;
		this->bitsPerSample = 8;
	}
	if (format == AL_FORMAT_STEREO16) {
		this->channels = 2;
		this->bitsPerSample = 16;
	}

	this->frequency = freq;

	if (start > 0.0f && end > start) {
		float bytesPerSecond = (freq * bitsPerSample) / 8.0f;
		int begin = start * bytesPerSecond * channels;
		int endI = end * bytesPerSecond * channels;

		std::vector<uint16_t> copy(endI - begin);
		for (int i = 0; i < (endI - begin) -1; i++) {
			copy[i] = rawData[begin + i];
		}

		rawData.resize(endI - begin);

		for (int i = 0; i < copy.size(); i++) {
			rawData[i] = copy[i];
		}
	}

	alGetError();
	alBufferData(bufferID, format, rawData.data(), rawData.size() * sizeof(rawData[0]), freq);
	if ((err = alGetError()) != AL_NO_ERROR) {
		printf("ERROR: alBufferData : %s\n\tIn SoundData(id = %d) filepath constructor", getALerrorString(err), bufferID);
		alDeleteBuffers(1, &bufferID);
		return;
	}

}

SoundData::SoundData(const std::vector<uint16_t>& rawData, int frequency, int bitsPerSample, int channels)
{
	this->rawData.resize(rawData.size());
	memcpy_s(this->rawData.data(), this->rawData.size() * sizeof(uint16_t), rawData.data(), rawData.size() * sizeof(uint16_t));

	ALenum format;
	if (channels == 1 && bitsPerSample == 8) format = AL_FORMAT_MONO8;
	if (channels == 1 && bitsPerSample == 16) format = AL_FORMAT_MONO16;
	if (channels > 1 && bitsPerSample == 8) format = AL_FORMAT_STEREO8;
	if (channels > 1 && bitsPerSample == 16) format = AL_FORMAT_STEREO16;

	this->frequency = frequency;
	this->bitsPerSample = bitsPerSample;
	this->channels = channels;

	ALenum err;
	alGetError();
	alBufferData(bufferID, format, rawData.data(), rawData.size() * sizeof(uint16_t), frequency);
	if ((err = alGetError()) != AL_NO_ERROR) {
		printf("ERROR: alBufferData : %s\n\tIn SoundData(id = %d) filepath constructor", getALerrorString(err), bufferID);
		alDeleteBuffers(1, &bufferID);
		return;
	}
}

SoundData::SoundData(SoundData& sound)
{
}

SoundData::~SoundData()
{
	alDeleteBuffers(1, &bufferID);
}

std::vector<unsigned char>& SoundData::getRawData()
{
	return rawData;
}

int SoundData::getFrequency()
{
	return frequency;
}

int SoundData::getBitsPerSample()
{
	return bitsPerSample;
}

int SoundData::getChannels()
{
	return channels;
}

float SoundData::getDuration()
{
	return ((rawData.size() * sizeof(uint16_t)) / bitsPerSample) * frequency;
}

ALuint SoundData::getBufferID()
{
	return bufferID;
}

// work in progress...
void SoundData::saveToFile(const std::string& filepath)
{
	AudioFile<double>::AudioBuffer buffer;
	buffer.resize(channels);
	for (int ch = 0; ch < buffer.size(); ch++) {
		int bytesPerSample = bitsPerSample / 8;
		int samplesPerChannel = (rawData.size() / channels) / bytesPerSample;
		buffer[ch].resize(samplesPerChannel);

		for (int i = 0; i < samplesPerChannel; i++) {

			int rawDataIndex = ((i * channels + ch) * bytesPerSample);
			
			if (bitsPerSample == 8) {
				uint8_t* beginRead = &rawData[rawDataIndex];
				buffer[ch][i] = ((double)(*beginRead)) / 32767.0;
			}
			else if (bitsPerSample == 16) {
				uint16_t* beginRead = (uint16_t*) &rawData[rawDataIndex];
				buffer[ch][i] = ((double)(*beginRead)) / 32767.0;
			}
			else {
				printf("Could not save %s because %d bits per sample is not supported\n", filepath.c_str(), bitsPerSample);
			}
			//buffer[ch][i] *= 32767;
		}

	}

	AudioFile<double> file;
	file.setAudioBuffer(buffer);
	file.setBitDepth(bitsPerSample);
	file.setNumChannels(channels);
	file.setSampleRate(frequency);

	if (!file.save(filepath, AudioFileFormat::Wave)) {
		printf("failed to save: %s\n", filepath);
	}
}

bool SoundData::loadWave(const std::string& filepath, ALenum& format, ALsizei& freq, ALsizei& size) {

	AudioFile<float> wav;
	wav.load(filepath.c_str());

	int sampleRate = wav.getSampleRate();
	int bitDepth = wav.getBitDepth();
	int numOfSamples = wav.getNumSamplesPerChannel();
	double lengthInSeconds = wav.getLengthInSeconds();
	
	int numChannels = wav.getNumChannels();
	bool isMono = wav.isMono();
	bool isStereo = wav.isStereo();

	if (isMono) {
		if (bitDepth == 8) {
			//format = AL_FORMAT_MONO8;
			format = AL_FORMAT_MONO16;
			bitDepth = 16;
		}
		else format = AL_FORMAT_MONO16;
	}
	
	else if (isStereo){
		if (bitDepth == 8) format = AL_FORMAT_STEREO8;
		else format = AL_FORMAT_STEREO16;
	}
	else {
		return false;
	}

	freq = sampleRate;


	if (isMono) {
		if (bitDepth == 8) {
			rawData.resize(wav.samples[0].size());
			for (int i = 0; i < wav.samples[0].size(); i++) {
				rawData[i] = (uint8_t)(wav.samples[0][i] * 255.0); 
			}
		}
		else if (bitDepth == 16) {
			rawData.resize(wav.samples[0].size() * 2);
			for (int i = 0; i < wav.samples[0].size(); i += 2) {

				uint16_t* beginWrite = (uint16_t*)&rawData[i];
				*beginWrite = wav.samples[0][i / 2] * 32767;

			}
		}
		else {
			printf("bit depth was not 8 or 16\n");
			return false;
		}
	}
	else {
		if (bitDepth == 8) {
			rawData.resize(wav.samples[0].size() * 2);
			for (int i = 0; i < wav.samples[0].size(); i++) {

				rawData[i * 2 + 0] = wav.samples[0][i] * 32767;
				rawData[i * 2 + 1] = wav.samples[1][i] * 32767;

			}
		}
		else if (bitDepth == 16) {
			rawData.resize(wav.samples[0].size() * 4);
			for (int i = 0; i < wav.samples[0].size(); i++) {

				uint16_t* beginWrite1 = (uint16_t*)&rawData[i * 4 + 0];
				uint16_t* beginWrite2 = (uint16_t*)&rawData[i * 4 + 2];

				*beginWrite1 = wav.samples[0][i] * 32767;
				*beginWrite2 = wav.samples[1][i] * 32767;

			}
		}
	}

	size = rawData.size() * sizeof(rawData[0]);
	channels = numChannels;

	return true;
}

std::string SoundData::getALerrorString(ALenum errorCode) {
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
