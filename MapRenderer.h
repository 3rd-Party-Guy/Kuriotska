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
public:
	MapRenderer(Map* map, Player* player);
	~MapRenderer();
	void RenderMap() const;
};