#include <iostream>
#include <unordered_map>

#include <curses.h>

#include "MapRenderer.h"

std::unordered_map<MapNodeType, char> mapNodeTypeGraphicLookup = {
	{ MapNodeType::Grass, 'g' },
	{ MapNodeType::Stone, 's' },
	{ MapNodeType::Water, '~' }
};

MapRenderer::MapRenderer(Map map) : map(map) {
	int maxX = getmaxx(stdscr);
	int maxY = getmaxy(stdscr);
	mapWindow = newwin(map.sizeY + 10, map.sizeX + 10, maxY / 2 - map.sizeY / 2, maxX / 2 - map.sizeX / 2);
	keypad(mapWindow, true);
	box(mapWindow, 0, 0);
}

MapRenderer::~MapRenderer() {
	delwin(mapWindow);
}

void MapRenderer::RenderMap() {
	wclear(mapWindow);

	for (size_t y = 0; y < map.sizeY; ++y) {
		for (size_t x = 0; x < map.sizeX; ++x) {
			mvaddch(y, x, mapNodeTypeGraphicLookup[map.GetNode(x, y).GetType()]);
		}
	}

	refresh();
}