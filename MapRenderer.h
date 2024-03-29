#pragma once

#include <curses.h>
#include <unordered_map>

#include "Vector2.h"
#include "Player.h"
#include "Map.h"

class MapRenderer
{
private:
	WINDOW* mapWindow;
	Map* map;
	Player* player;

	const Vector2<unsigned short> winSize;
	Vector2<int> position;
	const int centerBuffer = 3;																		// When to Re-Center Window (see definition of CenterSelf())

	int minPlayerPosDifX;
	int maxPlayerPosDifX;
	int minPlayerPosDifY;
	int maxPlayerPosDifY;

	Vector2<int> halfWinSize;

	static std::unordered_map<MapNodeType, char> mapNodeTypeGraphicLookup;
	static std::unordered_map<MapNodeType, int> mapNodeTypeColorLookup;
	bool IsOutOfBounds(int mapCoordX, int mapCoordY) const;
	bool IsOutOfBounds(Vector2<int> mapPos) const;

	void RenderNode(Vector2<int> mapPos, int colorID, chtype graphic) const;

	void RenderTerrain() const;
	void RenderEnemies() const;
	void RenderPlayerAttacks() const;
	void RenderPlayer() const;
public:
	MapRenderer(Map* map, Player* player, unsigned short winSizeX, unsigned short winSizeY);
	~MapRenderer();
	void RenderMap() const;
	void CenterSelf();
};