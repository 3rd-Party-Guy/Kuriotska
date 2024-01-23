#include <stdio.h>
#include <curses.h>

#include "Player.h"
#include "Map.h"
#include "MapRenderer.h"
#include "InputHandler.h"
#include "PerlinNoise.h"

#define MAP_WINDOW_WIDTH 40
#define MAP_WINDOW_HEIGHT 25

int main(int argc, const char** argv) {
	printf("\033[?1003h\n");

	// Initialization curses 
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	curs_set(0);
	refresh();

	// Initialization game
	PerlinNoise::SetPrimeIndex(7);
	Player player;
	Map map(40, 20);
	MapRenderer mapRenderer(&map, &player, MAP_WINDOW_WIDTH, MAP_WINDOW_HEIGHT);
	InputHandler inputHandler(&player);

	bool run = true;
	while (run) {
		inputHandler.HandleInput();
		mapRenderer.RenderMap();
	}

	exit(0);
}