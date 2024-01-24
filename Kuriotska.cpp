#include <stdio.h>
#include <iostream>
#include <curses.h>
#include <chrono>

#include "Player.h"
#include "Map.h"
#include "MapRenderer.h"
#include "InputHandler.h"
#include "PerlinNoise.h"
#include "Debugger.h"
#include "Misc.h"

#define MAP_WINDOW_WIDTH 40
#define MAP_WINDOW_HEIGHT 20

bool isInitialized = false;

std::string loadingStatusArr[10] = {
	"Generating World...\nStay put!",
	"Still generating...\nThis can take some time.",
	"Just wait a second...",
	"What I'm doing is really important right now...",
	"Be patient!!!!!",
	"... So how's your day?",
	"Just kidding. I don't care.",
	"Okay that was a bit mean...\nSorry...",
	"This is getting awkward...",
	"Maybe go drink a coffee or something?"
};

void ChangeInitColorRec(bool isOn, int statusIndex) {
	using namespace std::chrono_literals;
	if (isInitialized) return;

	clear();
	if (isOn) attroff(A_STANDOUT);
	else attron(A_STANDOUT);
	addstr(loadingStatusArr[statusIndex].c_str());
	refresh();

	std::this_thread::sleep_for(2s);
	ChangeInitColorRec(!isOn, (statusIndex + 1) % 10);
}

int main(int argc, const char** argv) {
	printf("\033[?1003h\n");

	// Initialization curses 
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr, true);
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

	// Initialization game
	attron(COLOR_PAIR(4));
	std::thread loadingThread(ChangeInitColorRec, true, 0);

	PerlinNoise::SetPrimeIndex(Misc::RandomInRange(0, 9));
	Map map(1000, 1000);

	// Spawn Player on Random Sand Node
	Player player(0, 0);
	while (true) {
		Vector2<int> randPos(Misc::RandomInRange(0, 999), Misc::RandomInRange(0, 999));
		const MapNode* randNode = map.GetNode(randPos);
		if (randNode->GetType() == MapNodeType::Sand) {
			player.SetPositionAbs(randNode->GetPosition());
			break;
		}
	}

	MapRenderer mapRenderer(&map, &player, MAP_WINDOW_WIDTH, MAP_WINDOW_HEIGHT);
	InputHandler inputHandler(&player);
	Debugger::instance();

	isInitialized = true;
	clear();
	attroff(COLOR_PAIR(4));

	bool run = true;
	while (run) {
		inputHandler.HandleInput();
		mapRenderer.RenderMap();
		mapRenderer.CenterSelf();
	}

	exit(0);
}