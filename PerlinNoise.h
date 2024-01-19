#pragma once

#include <vector>
#include "Vector2.h"

#define MAX_PRIME_INDEX 10
#define NUM_OCTAVES 7
#define PERSISTENCE 0.5

class PerlinNoise
{
private:
	static const int primes[MAX_PRIME_INDEX][3];
	int primeIndex;

	double Interpolate(double a, double b, double x);
	double Noise(int i, int x, int y);
	double SmoothNoise(int i, int x, int y);
	double InterpolatedNoise(int i, double x, double y);
public:
	PerlinNoise();
	PerlinNoise(int primeIndex);
	double GetCoordValue2D(double x, double y);
};