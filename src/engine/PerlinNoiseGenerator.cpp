#include "PerlinNoiseGenerator.h"

#include "PerlinNoise.hpp"
#include <random>
#include <time.h>

PerlinNoiseGenerator::PerlinNoiseGenerator() :
    PerlinNoiseGenerator(0, 8, 8.0f)
{
    srand(time(NULL));
    setSeed(rand());
}

PerlinNoiseGenerator::PerlinNoiseGenerator(int seed) :
    PerlinNoiseGenerator(seed, 8, 8.0f)
{
}

PerlinNoiseGenerator::PerlinNoiseGenerator(int seed, int octaves, float frequency) :
    seed(seed),
    octaves(octaves),
    frequency(frequency),
    perlin(siv::PerlinNoise(std::mt19937()))
{
    perlin.reseed((double)seed);
}

void PerlinNoiseGenerator::setSeed(int seed)
{
    this->seed = seed;
    perlin.reseed((double)seed);
}

float PerlinNoiseGenerator::getSeed()
{
    return seed;
}

void PerlinNoiseGenerator::setOctaves(int octaves)
{
    this->octaves = octaves;
}

int PerlinNoiseGenerator::getOctaves()
{
    return octaves;
}

void PerlinNoiseGenerator::setFrequency(float frequency)
{
    this->frequency = frequency;
}

float PerlinNoiseGenerator::getFrequency()
{
    return frequency;
}

void PerlinNoiseGenerator::setScaleX(float sx)
{
    scaleX = sx;
}

void PerlinNoiseGenerator::setScaleY(float sy)
{
    scaleY = sy;
}

float PerlinNoiseGenerator::getScaleX()
{
    return scaleX;
}

float PerlinNoiseGenerator::getScaleY()
{
    return scaleY;
}

float PerlinNoiseGenerator::getValueAt(float x, float y)
{
    x *= scaleX;
    y *= scaleY;
    return (float)perlin.accumulatedOctaveNoise2D_0_1((double)x / frequency, (double)y / frequency, (double)octaves);
}
