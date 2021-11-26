#pragma once

#include <vector>
#include <chrono>

class FrameRateTimer {
public:
	// frame rate, delta time, and update time will be averaged over the given number of frames
	FrameRateTimer(int frameAveragingSampleSize = 10);
	~FrameRateTimer();

	// call this method at the beginning of each frame before glfwPollEvents
	void updatePerFrameBegin();

	// call this method at the end of each frame
	void updatePerFrameEnd();


	// averages the fps, deltaTime, and updateTime over the last x number of frames
	void setFrameAveragingSampleSize(int x);


	// returns the averaged frame rate
	float getFPS();

	// returns the averaged delta time in milliseconds
	float getDeltaTime();

	// returns unaveraged delta time in seconds
	float getDeltaSeconds();

	// returns the averaged update time
	float getUpdateTime();

private:

	void calculateFPS();
	void calculateDeltaTime();
	void calculateUpdateTime();

private:
	int framesSinseLastSampleSizeUpdate = 0;
	int framePoolItter = 0;
	std::vector<float> framePool;
	std::vector<float> updateTimePool;
	std::vector<float> deltaTimePool;
	float fps = 0.0f;
	float deltaTime= 0.0f;
	float updateTime = 0.0f;
	float deltaSeconds = 0.0f;

	std::chrono::high_resolution_clock clock;
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::time_point<std::chrono::steady_clock> startUpdateTIme;
};