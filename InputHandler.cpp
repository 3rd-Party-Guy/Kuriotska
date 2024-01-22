#include <curses.h>

#include "InputHandler.h"

std::unordered_map<int, InputAction> InputHandler::InputActionLookup;

void InputHandler::HandleInput() {
	curChar = getch();
	if (curChar == ERR) return;

	std::unordered_map<int, InputAction>::const_iterator iter = InputActionLookup.find(curChar);
	if (iter != InputActionLookup.end())
		iter->second();
}

InputHandler::InputHandler(Player* player) : player(player) {
	curChar = 0;

	InputActionLookup = {
		{ 'w', [this]() { MoveActionRel(0, -1); } },
		{ 'W', [this]() { MoveActionRel(0, -1); } },
		{ 'a', [this]() { MoveActionRel(-1, 0); } },
		{ 'A', [this]() { MoveActionRel(-1, 0); } },
		{ 's', [this]() { MoveActionRel(0, 1); } },
		{ 'S', [this]() { MoveActionRel(0, 1); } },
		{ 'd', [this]() { MoveActionRel(1, 0); } },
		{ 'D', [this]() { MoveActionRel(1, 0); } }
	};
}

void InputHandler::MoveActionRel(int x, int y) {
	player->MoveRel(x, y);
}

void InputHandler::MoveActionAbs(int x, int y) {
	player->MoveAbs(x, y);
}