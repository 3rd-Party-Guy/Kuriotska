#pragma once

#include <unordered_map>
#include <memory>

#include "Player.h"
#include "Command.h"

class InputHandler
{
private:
	Player* player;
	int curChar;
	static std::unordered_map<int, std::unique_ptr<Command>> InputActionLookup;
public:
	void HandleInput();
	InputHandler(Player* player);
};