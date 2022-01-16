#pragma once

#include "PerlinNoise.hpp"

class PerlinNoiseGenerator {
public:
	PerlinNoiseGenerator();
	PerlinNoiseGenerator(int seed);
	PerlinNoiseGenerator(int seed, int octaves, float frequency);

	void setSeed(int seed);
	float getSeed();

	void setOctaves(int octaves);
	int getOctaves();

	void setFrequency(float frequency);
	float getFrequency();

	void setScaleX(float sx);
	void setScaleY(float sy);
	float getScaleX();
	float getScaleY();

	float getValueAt(float x, float y);

private:
	int seed = 0;
	int octaves = 8;
	float frequency = 8.0f;

	float scaleX = 0, scaleY = 0;

	siv::PerlinNoise perlin;

};
