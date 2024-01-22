#include <stdio.h>
#include <curses.h>

#include "Player.h"
#include "Map.h"
#include "MapRenderer.h"
#include "InputHandler.h"
#include "PerlinNoise.h"

int main(int argc, const char** argv) {
	printf("\033[?1003h\n");

	// Initialization curses 
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	refresh();

	// Initialization game
	PerlinNoise::SetPrimeIndex(7);
	Player player;
	Map map(40, 20);
	MapRenderer mapRenderer(&map, &player);
	InputHandler inputHandler(&player);

	bool run = true;
	while (run) {
		inputHandler.HandleInput();
		mapRenderer.RenderMap();
	}
	getch();

	exit(0);
}