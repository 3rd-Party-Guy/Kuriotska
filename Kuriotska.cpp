#include <stdio.h>
#include <iostream>
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

	if (!has_colors())
		std::cerr << "FATAL ERROR: Your terminal does not support colors.\nExiting.";

	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_CYAN, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_CYAN);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_WHITE, COLOR_RED);
	init_pair(5, COLOR_WHITE, COLOR_GREEN);

	refresh();

	// Initialization game
	PerlinNoise::SetPrimeIndex(1);
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