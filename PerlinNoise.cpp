#include <numeric>
#include <random>
#include <math.h>
#include <stdexcept>

#include "PerlinNoise.h"

#define DEFAULT_SEED 456

const int PerlinNoise::primes[MAX_PRIME_INDEX][3] = {
		{ 995615039, 600173719, 701464987 },
		{ 831731269, 162318869, 136250887 },
		{ 174329291, 946737083, 245679977 },
		{ 362489573, 795918041, 350777237 },
		{ 457025711, 880830799, 909678923 },
		{ 787070341, 177340217, 593320781 },
		{ 405493717, 291031019, 391950901 },
		{ 458904767, 676625681, 424452397 },
		{ 531736441, 939683957, 810651871 },
		{ 997169939, 842027887, 423882827 }
};

int PerlinNoise::primeIndex = 0;

void PerlinNoise::SetPrimeIndex(int primeSeed) {
	if (primeSeed > MAX_PRIME_INDEX - 1 || primeSeed < 0) {
		throw std::runtime_error("Fatal Error: Perlin Noise OBJ generated with invalid Prime Index.");
	}

	primeIndex = primeSeed;
}

// Get a random number between 0 and 1
double PerlinNoise::Noise(int i, int x, int y) {
	int n = x + y * 57;
	n = (n << 13) ^ n;
	int a = primes[i][0], b = primes[i][1], c = primes[i][2];
	int t = (n * (n * n * a + b) + c) & 0x7fffffff;

	return 1.0 - (double)t / 1073741824.0;
}

double PerlinNoise::SmoothNoise(int i, int x, int y) {
	double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) + Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16;
	double sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) + Noise(i, x, y + 1)) / 8;
	double center = Noise(i, x, y) / 4;

	return corners + sides + center;
}

// Cosine Interpolation
double PerlinNoise::Interpolate(double a, double b, double x) {
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5;

	return a * (1 - f) + b * f;
}

double PerlinNoise::InterpolatedNoise(int i, double x, double y) {
	int ix = (int)x;
	int iy = (int)y;
	double fracX = x - (double)ix;
	double fracY = y - (double)iy;

	double v1 = SmoothNoise(i, ix	 , iy	 );
	double v2 = SmoothNoise(i, ix + 1, iy	 );
	double v3 = SmoothNoise(i, ix	 , iy + 1);
	double v4 = SmoothNoise(i, ix + 1, iy + 1);

	double i1 = Interpolate(v1, v2, fracX);
	double i2 = Interpolate(v3, v4, fracX);

	return Interpolate(i1, i2, fracY);
}

double PerlinNoise::GetCoordValue2D(double x, double y) {
	double total = 0;
	double frequency = pow(2, NUM_OCTAVES);
	double amplitude = 1;
	for (int i = 0; i < NUM_OCTAVES; ++i) {
		frequency /= 2;
		amplitude *= PERSISTENCE;
		total += InterpolatedNoise((primeIndex + i) % MAX_PRIME_INDEX,
			x / frequency,
			y / frequency) * amplitude;
	}

	return total / frequency;
}