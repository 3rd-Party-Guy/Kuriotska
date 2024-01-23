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

	static std::unordered_map<MapNodeType, char> mapNodeTypeGraphicLookup;
	static std::unordered_map<MapNodeType, int> mapNodeTypeColorLookup;

public:
	MapRenderer(Map* map, Player* player, unsigned short winSizeX, unsigned short winSizeY);
	~MapRenderer();
	void RenderMap() const;
	void CenterSelf();
};