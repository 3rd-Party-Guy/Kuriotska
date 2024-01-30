#pragma once

#include <algorithm>
#include <random>

#include "Map.h"
#include "MapNode.h"
#include "Vector2.h"

struct Misc {
	static int MapToInt(double value, double x1, double y1, int x2, int y2) {
		value = std::max(x1, std::min(y1, value));
		double denominator = (y1 - x1) != 0 ? (y1 - x1) : 1.0;
		double normalizedValue = (value - x1) / denominator;

		if (normalizedValue < 0.0) return x2;
		if (normalizedValue > 1.0) return y2;

		return x2 + static_cast<int>(normalizedValue * (y2 - x2 + 1));
	}

	static int RandomInRange(const int minInclusive, const int maxInclusive) {
		static thread_local std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<int> dist(minInclusive, maxInclusive);

		return dist(gen);
	}

	static int CalculateDistanceEuclidean(const Vector2<int> a, const Vector2<int> b) {
		double distance = sqrt(pow(b.GetX() - a.GetX(), 2) + pow(b.GetY() - a.GetY(), 2));
		return (int)std::floor(distance);
	}

	// This function counts a diagonal move as two straight moves
	static int CalculateDistanceManhattan(const Vector2<int> a, const Vector2<int> b) {
		int distance = abs(b.GetX() - a.GetX()) + abs(b.GetY() - a.GetY());
		return (int)distance;
	}

	static const MapNode* GetNextNodeTowardsTarget(const Map* map, const MapNode* curNode, const MapNode* targetNode) {
		Vector2<int> curPos = curNode->GetPosition();
		Vector2<int> targetPos = targetNode->GetPosition();

		Vector2<int> nextPosUnit(0, 0);

		if (targetPos.GetX() < curPos.GetX()) nextPosUnit.SetX(-1);
		else if (targetPos.GetX() > curPos.GetX()) nextPosUnit.SetX(1);

		if (targetPos.GetY() < curPos.GetX()) nextPosUnit.SetY(-1);
		else if (targetPos.GetY() > curPos.GetY()) nextPosUnit.SetY(1);

		return map->GetNode(curPos + nextPosUnit);
	}

	static const MapNode* GetNextNodeTowardsTarget(const Map* map, const Vector2<int> curPos, const Vector2<int> targetPos) {
		const MapNode* curNode = map->GetNode(curPos);
		const MapNode* targetNode = map->GetNode(targetPos);

		return GetNextNodeTowardsTarget(map, curNode, targetNode);
	}

	static const Vector2<int> GetUnitVecTowardsTarget(const Vector2<int> curPos, const Vector2<int> targetPos) {
		Vector2<int> nextPosUnit(0, 0);

		if (targetPos.GetX() < curPos.GetX()) nextPosUnit.SetX(-1);
		else if (targetPos.GetX() > curPos.GetX()) nextPosUnit.SetX(1);

		if (targetPos.GetY() < curPos.GetY()) nextPosUnit.SetY(-1);
		else if (targetPos.GetY() > curPos.GetY()) nextPosUnit.SetY(1);
		
		return nextPosUnit;
	}
};