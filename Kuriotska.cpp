#include <iostream>
#include <unordered_map>
#include <utility>
#include <time.h>

#include "Map.h"
#include "MapRenderer.h"

int main(int argc, const char** argv) {
	// Initialization
	srand(time(0));

	Map map(80, 40);
	MapRenderer mapRenderer(map);

	mapRenderer.RenderMap();

	return 0;
}