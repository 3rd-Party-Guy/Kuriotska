#pragma once

#include "Map.h"

class MapRenderer
{
private:
	Map map;
public:
	MapRenderer(Map map);
	~MapRenderer();
	void RenderMap();
};