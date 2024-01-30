#pragma once

#include <thread>
#include <chrono>

#include "Entity.h"
#include "Vector2.h"

class Attack : public Entity
{
private:
	int orbitRadius;
	int curPosIndex;

	int damageAmount;

	std::chrono::milliseconds moveCooldown;

	const Entity* target;
	std::thread updateThread;

	Vector2<int> CalculatePosition();

public:
	Attack(Entity* target, int orbitRadius, int moveCooldown, int damageAmount);
	void Update();
};