#include <curses.h>

#include "Map.h"
#include "MapRenderer.h"
#include "PerlinNoise.h"

int main(int argc, const char** argv) {
	initscr();
	cbreak();
	noecho();
	refresh();

	getch();

	// Initialization
	PerlinNoise::SetPrimeIndex(5);

	Map map(20, 20);
	MapRenderer mapRenderer(map);
	mapRenderer.RenderMap();

	getch();

	exit(0);
}