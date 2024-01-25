#pragma once

#include <curses.h>

#include "Player.h"

class PlayerInfoRenderer
{
private:
	WINDOW* infoWindow;
	const Player* player;
	void RenderHealth() const;
	void RenderAir() const;
public:
	void RenderInfo() const;
	PlayerInfoRenderer(Player* player, int mapWinSizeX, int mapWinSizeY);
};