#pragma once

#include <algorithm>
#include <random>

#include "MapNode.h"
#include "Vector2.h"

struct Misc {
	static int MapFloatToInt(float value, float x1, float y1, int x2, int y2) {
		value = std::max(x1, std::min(y1, value));
		float normalizedValue = (value - x1) / (y1 - x1);

		return static_cast<int>(x2 + normalizedValue * (y2 - x2 + 1));
	}

	static int MapDoubleToInt(double value, double x1, double y1, int x2, int y2) {
		value = std::max(x1, std::min(y1, value));
		double normalizedValue = (value - x1) / (y1 - x1);

		return static_cast<int>(x2 + normalizedValue * (y2 - x2 + 1));
	}

	static int RandomInRange(const int minInclusive, const int maxInclusive) {
		static thread_local std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<int> dist(minInclusive, maxInclusive);

		return dist(gen);
	}

	// This function counts a diagonal move as two straight moves
	static int CalculateNodesDistance(const MapNode* a, const MapNode* b) {
		Vector2<int> aPos = a->GetPosition();
		Vector2<int> bPos = b->GetPosition();

		return abs((aPos.GetX() + aPos.GetY()) - (bPos.GetX() + bPos.GetY()));
	}
};