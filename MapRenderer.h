#pragma once

#include <curses.h>

#include "Map.h"

class MapRenderer
{
private:
	WINDOW* mapWindow;
	Map map;
public:
	MapRenderer(Map map);
	~MapRenderer();
	void RenderMap();
};