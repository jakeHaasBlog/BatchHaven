#include "FrameRateTimer.h"

FrameRateTimer::FrameRateTimer(int frameAveragingSampleSize) :
	framePool(std::vector<float>(frameAveragingSampleSize)),
	updateTimePool(std::vector<float>(frameAveragingSampleSize)),
	deltaTimePool(std::vector<float>(frameAveragingSampleSize))
{
	start = clock.now();
	end = clock.now();
	startUpdateTIme = clock.now();
	framesSinseLastSampleSizeUpdate = 0;
	framePoolItter = 0;
}

FrameRateTimer::~FrameRateTimer()
{
}

void FrameRateTimer::updatePerFrameBegin()
{
	if (framesSinseLastSampleSizeUpdate < framePool.size())
		framesSinseLastSampleSizeUpdate++;


	startUpdateTIme = clock.now();

	end = clock.now();
	float deltaTime = (float)((float)(end - start).count() / 1000000.0f);
	start = clock.now();

	deltaSeconds = deltaTime / 1000.0f;

	deltaTimePool[framePoolItter] = deltaTime;

	float fps = (1.0f / deltaTime) * 1000.0f;
	framePool[framePoolItter] = fps;

	framePoolItter++;
	if (framePoolItter >= framesSinseLastSampleSizeUpdate)
		framePoolItter = 0;
}

void FrameRateTimer::updatePerFrameEnd()
{
	float updateTime = (float)(((double)(clock.now() - startUpdateTIme).count()) / 1000000.0f);
	updateTimePool[framePoolItter] = updateTime;

	calculateUpdateTime();
	calculateDeltaTime();
	calculateFPS();
}

void FrameRateTimer::setFrameAveragingSampleSize(int x)
{
	framePool.resize(x);
	updateTimePool.resize(x);
	deltaTimePool.resize(x);
	framesSinseLastSampleSizeUpdate = 0;
	framePoolItter = 0;
}

float FrameRateTimer::getFPS()
{
	return fps;
}

float FrameRateTimer::getDeltaTime()
{
	return deltaTime;
}

float FrameRateTimer::getDeltaSeconds()
{
	return deltaSeconds;
}

float FrameRateTimer::getUpdateTime()
{
	return updateTime;
}

void FrameRateTimer::calculateFPS()
{
	float ftime = 0.0f;
	for (int i = 0; i < framesSinseLastSampleSizeUpdate; i++) {
		ftime += framePool[i];
	}
	fps = ftime / framesSinseLastSampleSizeUpdate;
}

void FrameRateTimer::calculateDeltaTime()
{
	float dtime = 0.0f;
	for (int i = 0; i < framesSinseLastSampleSizeUpdate; i++) {
		dtime += deltaTimePool[i];
	}
	deltaTime = dtime / framesSinseLastSampleSizeUpdate;
}

void FrameRateTimer::calculateUpdateTime()
{
	float utime = 0.0f;
	for (int i = 0; i < framesSinseLastSampleSizeUpdate; i++) {
		utime += updateTimePool[i];
	}
	updateTime = utime / framesSinseLastSampleSizeUpdate;
}
