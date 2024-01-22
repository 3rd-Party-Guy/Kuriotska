#pragma once

#include <unordered_map>
#include <functional>

#include "Player.h"

using InputAction = std::function<void()>;

class InputHandler
{
private:
	Player* player;
	int curChar;
	static std::unordered_map<int, InputAction> InputActionLookup;
	void MoveActionRel(int x, int y);
	void MoveActionAbs(int x, int y);
public:
	void HandleInput();
	InputHandler(Player* player);
};