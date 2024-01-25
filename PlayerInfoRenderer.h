#pragma once

#include <curses.h>

#include "Player.h"

class PlayerInfoRenderer
{
private:
	WINDOW* infoWindow;
	const Player* player;
public:
	PlayerInfoRenderer(Player* player, int mapWinSizeX, int mapWinSizeY);
};