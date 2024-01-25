#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cmath>

#include <curses.h>

#include "MapRenderer.h"
#include "Vector2.h"

std::unordered_map<MapNodeType, char> MapRenderer::mapNodeTypeGraphicLookup = {
	{ MapNodeType::Grass, 'g' },
	{ MapNodeType::Sand, 's' },
	{ MapNodeType::Water, '~' },
	{ MapNodeType::Player, '+' }
};

std::unordered_map<MapNodeType, int> MapRenderer::mapNodeTypeColorLookup = {
	{ MapNodeType::Grass, 5 },
	{ MapNodeType::Sand, 3 },
	{ MapNodeType::Water, 2 },
	{ MapNodeType::Player, 1 }
};

MapRenderer::MapRenderer(Map* map, Player* player, unsigned short winSizeX, unsigned short winSizeY) :
	map(map), player(player), winSize(winSizeX, winSizeY), position(player->GetPosition()) {
	minPlayerPosDifX = (int)std::floor(winSize.GetX() / 2) * -1 + centerBuffer;
	maxPlayerPosDifX = (int)std::floor(winSize.GetX() / 2) - centerBuffer;
	minPlayerPosDifY = (int)std::floor(winSize.GetY() / 2) * -1 + centerBuffer;
	maxPlayerPosDifY = (int)std::floor(winSize.GetY() / 2) - centerBuffer;

	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	int startX = (maxX - winSizeX) / 2;
	int startY = (maxY - winSizeY) / 2;

	mapWindow = newwin(winSizeY, winSizeX, startY, startX);
}

MapRenderer::~MapRenderer() {
	delwin(mapWindow);
}

void MapRenderer::CenterSelf() {
	const int playerPosDifX = position.GetX() - player->GetPosition().GetX();
	const int playerPosDifY = position.GetY() - player->GetPosition().GetY();

	std::ostringstream debugInfo;

	debugInfo << playerPosDifX << ", " << playerPosDifY << "\n" <<
		minPlayerPosDifX << ", " << maxPlayerPosDifX << ", " << minPlayerPosDifY << ", " << maxPlayerPosDifY;

	if (playerPosDifX <= minPlayerPosDifX)
		position.SetX(position.GetX() + winSize.GetX() - centerBuffer * 2);
	else if (playerPosDifX > maxPlayerPosDifX)
		position.SetX(position.GetX() - winSize.GetX() + centerBuffer * 2);
	if (playerPosDifY <= minPlayerPosDifY)
		position.SetY(position.GetY() + winSize.GetY() - centerBuffer * 2);
	else if (playerPosDifY > maxPlayerPosDifY)
		position.SetY(position.GetY() - winSize.GetY() + centerBuffer * 2);
}

void MapRenderer::RenderMap() const {
	wclear(mapWindow);

	const Vector2<int> curPlayerPos = player->GetPosition();
	const int halfWinY = (int)std::floor(winSize.GetY() / 2);
	const int halfWinX = (int)std::floor(winSize.GetX() / 2);

	for (int y = -halfWinY; y < halfWinY; ++y) {
		for (int x = -halfWinX; x < halfWinX; ++x) {
			// Get Coordinate Values
			int mapCoordY = position.GetY() + y;
			int mapCoordX = position.GetX() + x;

			int mapWinCoordY = y + halfWinY;
			int mapWinCoordX = x + halfWinX;

			// Handle Outside Bounds
			if (mapCoordX < 0 || mapCoordX >= map->sizeX || mapCoordY < 0 || mapCoordY >= map->sizeY) {
				continue;
			}

			// Handle is Player at Coordinate
			if (mapCoordX == curPlayerPos.GetX() && mapCoordY == curPlayerPos.GetY()) {
				int colorID = mapNodeTypeColorLookup[MapNodeType::Player];
				wattron(mapWindow, COLOR_PAIR(colorID));
				mvwaddch(mapWindow, mapWinCoordY, mapWinCoordX, mapNodeTypeGraphicLookup.at(MapNodeType::Player));
				wattroff(mapWindow, COLOR_PAIR(colorID));
				continue;
			}

			// Draw Map Node at Coordinate
			const MapNodeType curNodeType = map->GetNode(mapCoordX, mapCoordY)->GetType();
			auto iterGraphic = mapNodeTypeGraphicLookup.find(curNodeType);
			if (iterGraphic != mapNodeTypeGraphicLookup.end()) {
				auto iterColor = mapNodeTypeColorLookup.find(curNodeType);
				int colorPairID = (iterColor != mapNodeTypeColorLookup.end()) ?
					mapNodeTypeColorLookup[curNodeType] : 0;

				wattron(mapWindow, COLOR_PAIR(colorPairID));
				mvwaddch(mapWindow, mapWinCoordY, mapWinCoordX, mapNodeTypeGraphicLookup[curNodeType]);
				wattroff(mapWindow, COLOR_PAIR(colorPairID));
			}
		}
	}

	wrefresh(mapWindow);
}