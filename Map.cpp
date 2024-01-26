#include <iostream>
#include <utility>

#include "Map.h"
#include "Misc.h"

const MapNode* Map::GetNode(int x, int y) const {
	auto iter = map.find(std::make_pair(x, y));

	if (iter != map.end())
		return &(iter->second);

	return nullptr;
}

const MapNode* Map::GetNode(Vector2<int> pos) const {
	return GetNode(pos.GetX(), pos.GetY());
}

const MapNode* Map::GetRandomNode() const {
	Vector2<int> randPos(Misc::RandomInRange(0, sizeX - 1), Misc::RandomInRange(0, sizeY - 1));

	return GetNode(randPos);
}

void Map::GenerateMap() {
	for (int x = 0; x < sizeX; ++x)
	for (int y = 0; y < sizeY; ++y) {
		map.emplace(std::make_pair(x, y), MapNode(Vector2<int>(x, y)));
	}
}

Map::Map() : sizeX(10), sizeY(10) {
	GenerateMap();
}
Map::Map(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {
	GenerateMap();
}