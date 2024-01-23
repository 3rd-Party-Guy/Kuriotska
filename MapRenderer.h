#pragma once

#include <curses.h>
#include <unordered_map>

#include "Player.h"
#include "Map.h"

class MapRenderer
{
private:
	WINDOW* mapWindow;
	Map* map;
	Player* player;
	const unsigned short winSizeX;
	const unsigned short winSizeY;

	static std::unordered_map<MapNodeType, char> mapNodeTypeGraphicLookup;
	static std::unordered_map<MapNodeType, int> mapNodeTypeColorLookup;
public:
	MapRenderer(Map* map, Player* player, unsigned short winSizeX, unsigned short winSizeY);
	~MapRenderer();
	void RenderMap() const;
};