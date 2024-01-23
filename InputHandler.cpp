#include <curses.h>

#include "InputHandler.h"

std::unordered_map<int, std::unique_ptr<Command>> InputHandler::InputActionLookup;

void InputHandler::HandleInput() {
	curChar = getch();
	if (curChar == ERR) return;

	auto iter = InputActionLookup.find(curChar);
	if (iter != InputActionLookup.end())
		iter->second->execute(player);
}

InputHandler::InputHandler(Player* player) : player(player) {
	curChar = 0;

	InputActionLookup.emplace('w', std::make_unique<MoveCommand>(0, -1, false)); 
	InputActionLookup.emplace('W', std::make_unique<MoveCommand>(0, -1, false));
	InputActionLookup.emplace(KEY_UP, std::make_unique<MoveCommand>(0, -1, false));
	InputActionLookup.emplace('a', std::make_unique<MoveCommand>(-1, 0, false));
	InputActionLookup.emplace('A', std::make_unique<MoveCommand>(-1, 0, false));
	InputActionLookup.emplace(KEY_LEFT, std::make_unique<MoveCommand>(-1, 0, false));
	InputActionLookup.emplace('s', std::make_unique<MoveCommand>(0, 1, false));
	InputActionLookup.emplace('S', std::make_unique<MoveCommand>(0, 1, false));
	InputActionLookup.emplace(KEY_DOWN, std::make_unique<MoveCommand>(0, 1, false));
	InputActionLookup.emplace('d', std::make_unique<MoveCommand>(1, 0, false));
	InputActionLookup.emplace('D', std::make_unique<MoveCommand>(1, 0, false));
	InputActionLookup.emplace(KEY_RIGHT, std::make_unique<MoveCommand>(1, 0, false));
	InputActionLookup.emplace('q', std::make_unique<ExitCommand>());
	InputActionLookup.emplace(27, std::make_unique<ExitCommand>());
}