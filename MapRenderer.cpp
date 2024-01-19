#include <iostream>
#include <unordered_map>

#include "MapRenderer.h"

std::unordered_map<MapNodeType, char> mapNodeTypeGraphicLookup = {
	{ MapNodeType::Grass, 'g' },
	{ MapNodeType::Stone, 's' },
	{ MapNodeType::Water, '~' }
};

MapRenderer::MapRenderer(Map map) : map(map) {
}

MapRenderer::~MapRenderer() {
}

void MapRenderer::RenderMap() {
	for (size_t y = 0; y < map.sizeY; ++y) {
		for (size_t x = 0; x < map.sizeX; ++x) {
			std::cout << mapNodeTypeGraphicLookup[map.GetNode(x, y).GetType()];
		}
		std::cout << std::endl;
	}
}