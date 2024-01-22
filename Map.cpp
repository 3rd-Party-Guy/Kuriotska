#include <iostream>
#include <utility>

#include "Map.h"

const MapNode* Map::GetNode(size_t x, size_t y) const {
	auto iter = map.find(std::make_pair(x, y));

	if (iter != map.end()) {
		return &(iter->second);
	}

	return nullptr;
}

void Map::GenerateMap() {
	for (size_t x = 0; x < sizeX; ++x)
	for (size_t y = 0; y < sizeY; ++y) {
		map.emplace(std::make_pair(x, y), MapNode(Vector2<int>(x, y)));
	}
}

Map::Map() : sizeX(10), sizeY(10) {
	GenerateMap();
}
Map::Map(size_t sizeX, size_t sizeY) : sizeX(sizeX), sizeY(sizeY) {
	GenerateMap();
}