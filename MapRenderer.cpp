#include <iostream>
#include <unordered_map>

#include <curses.h>

#include "MapRenderer.h"
#include "Vector2.h"

std::unordered_map<MapNodeType, char> MapRenderer::mapNodeTypeGraphicLookup = {
	{ MapNodeType::Grass, 'g' },
	{ MapNodeType::Stone, 's' },
	{ MapNodeType::Water, '~' },
	{ MapNodeType::Player, '+' }
};

std::unordered_map<MapNodeType, int> MapRenderer::mapNodeTypeColorLookup = {
	{ MapNodeType::Grass, 5 },
	{ MapNodeType::Stone, 3 },
	{ MapNodeType::Water, 2 },
	{ MapNodeType::Player, 1 }
};

MapRenderer::MapRenderer(Map* map, Player* player, unsigned short winSizeX, unsigned short winSizeY) :
		map(map), player(player), winSizeX(winSizeX), winSizeY(winSizeY) {
	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	int startX = (maxX - winSizeX) / 2;
	int startY = (maxY - winSizeY) / 2;

	mapWindow = newwin(winSizeY, winSizeX, startY, startX);
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
				int colorID = mapNodeTypeColorLookup[MapNodeType::Player];
				wattron(mapWindow, COLOR_PAIR(colorID));
				mvwaddch(mapWindow, y, x, mapNodeTypeGraphicLookup.at(MapNodeType::Player));
				wattroff(mapWindow, COLOR_PAIR(colorID));
				continue;
			}

			const MapNodeType curNodeType = map->GetNode(x, y)->GetType();
			auto iterGraphic = mapNodeTypeGraphicLookup.find(curNodeType);
			if (iterGraphic != mapNodeTypeGraphicLookup.end()) {
				auto iterColor = mapNodeTypeColorLookup.find(curNodeType);
				int colorPairID = (iterColor != mapNodeTypeColorLookup.end()) ?
					mapNodeTypeColorLookup[curNodeType] : 0;

				wattron(mapWindow, COLOR_PAIR(colorPairID));
				mvwaddch(mapWindow, y, x, mapNodeTypeGraphicLookup[curNodeType]);
				wattroff(mapWindow, COLOR_PAIR(colorPairID));
			}
		}
	}

	wrefresh(mapWindow);
}