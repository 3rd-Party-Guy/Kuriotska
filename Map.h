#pragma once

#include <map>
#include <utility>

#include "MapNode.h"

class Map {
private:
	std::map<std::pair<size_t, size_t>, MapNode> map;
public:
	const size_t sizeX, sizeY;
	MapNode GetNode(size_t x, size_t y);
	Map();
	Map(size_t sizeX, size_t sizeY);
	~Map();
};