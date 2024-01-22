#include <iostream>
#include <unordered_map>

#include <curses.h>

#include "MapRenderer.h"
#include "Vector2.h"

std::unordered_map<MapNodeType, char> mapNodeTypeGraphicLookup = {
	{ MapNodeType::Grass, 'g' },
	{ MapNodeType::Stone, 's' },
	{ MapNodeType::Water, '~' },
	{ MapNodeType::Player, '+' }
};

MapRenderer::MapRenderer(Map* map, Player* player) : map(map), player(player) {
	int maxX = getmaxx(stdscr);
	int maxY = getmaxy(stdscr);
	mapWindow = newwin(map->sizeY + 10, map->sizeX + 10, maxY / 2 - map->sizeY / 2, maxX / 2 - map->sizeX / 2);
	keypad(mapWindow, true);
	box(mapWindow, 0, 0);
}

MapRenderer::~MapRenderer() {
	delwin(mapWindow);
}

void MapRenderer::RenderMap() const {
	wclear(mapWindow);

	const Vector2<int> curPlayerPos = player->GetPosition();

	for (size_t y = 0; y < map->sizeY; ++y) {
		for (size_t x = 0; x < map->sizeX; ++x) {
			if (x == curPlayerPos.GetX() && y == curPlayerPos.GetY()) {
				mvaddch(y, x, mapNodeTypeGraphicLookup.at(MapNodeType::Player));
				continue;
			}

			const MapNodeType curNodeType = map->GetNode(x, y)->GetType();
			std::unordered_map<MapNodeType, char>::const_iterator iter = mapNodeTypeGraphicLookup.find(curNodeType);
			if (iter != mapNodeTypeGraphicLookup.end())
				mvaddch(y, x, mapNodeTypeGraphicLookup[curNodeType]);
		}
	}

	refresh();
}