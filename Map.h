#pragma once

#include <map>
#include <utility>

#include "MapNode.h"

class Map {
private:
	std::map<std::pair<int, int>, MapNode> map;
	void GenerateMap();
public:
	const int sizeX, sizeY;
	const MapNode* GetNode(int x, int y) const;
	const MapNode* GetNode(Vector2<int> pos) const;
	const MapNode* GetRandomNode() const;
	Map();
	Map(int sizeX, int sizeY);
};