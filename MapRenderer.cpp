#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cmath>

#include <curses.h>

#include "MapRenderer.h"
#include "Vector2.h"
#include "EnemyManager.h"

std::unordered_map<MapNodeType, char> MapRenderer::mapNodeTypeGraphicLookup = {
	{ MapNodeType::Grass, 'g' },
	{ MapNodeType::Sand, 's' },
	{ MapNodeType::Water, '~' },
	{ MapNodeType::Enemy, '!' },
	{ MapNodeType::Attack, '/' },
	{ MapNodeType::Player, '+' }
};

std::unordered_map<MapNodeType, int> MapRenderer::mapNodeTypeColorLookup = {
	{ MapNodeType::Grass, 5 },
	{ MapNodeType::Sand, 3 },
	{ MapNodeType::Water, 2 },
	{ MapNodeType::Attack, 9 },
	{ MapNodeType::Player, 1 },
	{ MapNodeType::Enemy, 8 }
};

MapRenderer::MapRenderer(Map* map, Player* player, unsigned short winSizeX, unsigned short winSizeY) :
	map(map), player(player), winSize(winSizeX, winSizeY), position(player->GetPosition()) {
	
	halfWinSize = Vector2<int>((int)std::floor(winSize.GetX() / 2), (int)std::floor(winSize.GetY() / 2));

	minPlayerPosDifX = halfWinSize.GetX() * -1 + centerBuffer;
	maxPlayerPosDifX = halfWinSize.GetX() - centerBuffer;
	minPlayerPosDifY = halfWinSize.GetY() * -1 + centerBuffer;
	maxPlayerPosDifY = halfWinSize.GetY() - centerBuffer;

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

bool MapRenderer::IsOutOfBounds(int mapCoordX, int mapCoordY) const {
	return (mapCoordX < 0 || mapCoordX >= map->sizeX || mapCoordY < 0 || mapCoordY >= map->sizeY);
}

bool MapRenderer::IsOutOfBounds(Vector2<int> mapPos) const {
	return IsOutOfBounds(mapPos.GetX(), mapPos.GetY());
}

void MapRenderer::RenderNode(Vector2<int> mapPos, int colorID, chtype graphic) const {
	const int winCoordPosX = (mapPos.GetX() - position.GetX()) + halfWinSize.GetX();
	const int winCoordPosY = (mapPos.GetY() - position.GetY()) + halfWinSize.GetY();

	wattron(mapWindow, COLOR_PAIR(colorID));
	mvwaddch(mapWindow, winCoordPosY, winCoordPosX, graphic);
	wattroff(mapWindow, COLOR_PAIR(colorID));
}

void MapRenderer::RenderTerrain() const {
	for (int y = -halfWinSize.GetY(); y < halfWinSize.GetY(); ++y) {
		for (int x = -halfWinSize.GetX(); x < halfWinSize.GetX(); ++x) {
			// Get Coordinate Values
			Vector2<int> mapPos(position.GetX() + x, position.GetY() + y);
			if (IsOutOfBounds(mapPos)) continue;

			const MapNodeType curNodeType = map->GetNode(mapPos)->GetType();
			chtype graphic = mapNodeTypeGraphicLookup[curNodeType];
			int colorID = mapNodeTypeColorLookup[curNodeType];

			RenderNode(mapPos, colorID, graphic);
		}
	}
}

void MapRenderer::RenderEnemies() const {
	const std::unordered_map<int, Enemy*>& enemies = EnemyManager::instance().GetEnemies();

	for (const std::pair<const int, Enemy*>& e : enemies) {
		if (IsOutOfBounds(e.second->GetPosition())) continue;

		const Vector2<int> curEnemyPos = e.second->GetPosition();
		int colorID = mapNodeTypeColorLookup[MapNodeType::Enemy];
		chtype graphic = mapNodeTypeGraphicLookup[MapNodeType::Enemy];

		RenderNode(curEnemyPos, colorID, graphic);
	}
}

void MapRenderer::RenderPlayerAttacks() const {
	const std::unordered_set<std::unique_ptr<Attack>>& playerAttacks = player->GetAttacks();
	chtype graphic = mapNodeTypeGraphicLookup[MapNodeType::Attack];
	int colorID = mapNodeTypeColorLookup[MapNodeType::Attack];

	for (const std::unique_ptr<Attack>& a : playerAttacks)
		RenderNode(a->GetPosition(), colorID, graphic);
}

void MapRenderer::RenderPlayer() const {
	int colorID = mapNodeTypeColorLookup[MapNodeType::Player];
	chtype graphic = mapNodeTypeGraphicLookup[MapNodeType::Player];
	const Vector2<int> curPlayerPos = player->GetPosition();
	
	RenderNode(curPlayerPos, colorID, graphic);

}

void MapRenderer::RenderMap() const {
	wclear(mapWindow);

	RenderTerrain();
	RenderEnemies();
	RenderPlayerAttacks();
	RenderPlayer();

	wrefresh(mapWindow);
}