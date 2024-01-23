#pragma once

#include <curses.h>

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
public:
	MapRenderer(Map* map, Player* player, unsigned short winSizeX, unsigned short winSizeY);
	~MapRenderer();
	void RenderMap() const;
};