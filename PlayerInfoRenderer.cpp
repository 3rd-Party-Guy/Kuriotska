#include "PlayerInfoRenderer.h"

PlayerInfoRenderer::PlayerInfoRenderer(Player* player, int mapWinSizeX, int mapWinSizeY) : player(player) {
	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	int padding = 2;

	int startX = (maxX - mapWinSizeX) / 2 - padding;
	int startY = (maxY - mapWinSizeY) / 2 + mapWinSizeY + 1;

	infoWindow = newwin(1, mapWinSizeX + padding * 2, startY, startX);
}

void PlayerInfoRenderer::RenderHealth() const {
	wattron(infoWindow, COLOR_PAIR(6));
	const int healthAmount = player->GetHealth();
	if (healthAmount <= 4) {
		wattron(infoWindow, A_STANDOUT);
		wattron(infoWindow, A_BLINK);
	}

	for (int i = 0; i < healthAmount; ++i) {
		mvwaddch(infoWindow, 0, i, '=');
	}

	wattroff(infoWindow, A_STANDOUT);
	wattroff(infoWindow, A_BLINK);
	wattroff(infoWindow, COLOR_PAIR(6));
}

void PlayerInfoRenderer::RenderAir() const {
	wattron(infoWindow, COLOR_PAIR(7));
	const int airAmount = player->GetAir();
	if (airAmount <= 4) {
		wattron(infoWindow, A_STANDOUT);
		wattron(infoWindow, A_BLINK);
	}

	for (int i = 0; i < player->GetAir(); ++i) {
		mvwaddch(infoWindow, 0, getmaxx(infoWindow) - i, '=');
	}

	wattroff(infoWindow, A_STANDOUT);
	wattroff(infoWindow, A_BLINK);
	wattroff(infoWindow, COLOR_PAIR(7));
}

void PlayerInfoRenderer::RenderInfo() const {
	wclear(infoWindow);
	RenderHealth();
	RenderAir();
	wrefresh(infoWindow);
}