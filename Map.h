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
	Map();
	Map(int sizeX, int sizeY);
};