#pragma once

#include <algorithm>

int MapFloatToInt(float value, float x1, float y1, int x2, int y2) {
	value = std::max(x1, std::min(y1, value));
	float normalizedValue = (value - x1) / (y1 - x1);

	return static_cast<int>(x2 + normalizedValue * (y2 - x2 + 1));
}


int MapDoubleToInt(double value, double x1, double y1, int x2, int y2) {
	value = std::max(x1, std::min(y1, value));
	double normalizedValue = (value - x1) / (y1 - x1);

	return static_cast<int>(x2 + normalizedValue * (y2 - x2 + 1));
}