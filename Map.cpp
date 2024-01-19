#include <iostream>
#include <utility>

#include "Map.h"

/*
	This function allows for lazy-initiation of the Nodes
*/
MapNode Map::GetNode(size_t x, size_t y) {
	try {
		return map.at({ x, y });
	}
	catch (const std::out_of_range&) {
		auto res = map.emplace(std::make_pair(x, y), MapNode(x, y));
		return res.first->second;
	}
}

Map::Map() : sizeX(10), sizeY(10) {
}
Map::Map(size_t sizeX, size_t sizeY) : sizeX(sizeX), sizeY(sizeY) {
}
Map::~Map() {
}