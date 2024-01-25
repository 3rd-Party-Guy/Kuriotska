#include "PlayerInfoRenderer.h"

PlayerInfoRenderer::PlayerInfoRenderer(Player* player, int mapWinSizeX, int mapWinSizeY) : player(player) {
	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	int startX = (maxX - mapWinSizeX) / 2 - 3;
	int startY = (maxY - mapWinSizeY) / 2 + 3;

	infoWindow = newwin(5, mapWinSizeX + 6, 0, 0);
	wclear(infoWindow);
	waddstr(infoWindow, "THIS WORKS");
	box(infoWindow, 0, 0);
	touchwin(infoWindow);
	wrefresh(infoWindow);
}