#pragma once

#include <thread>
#include <chrono>

#include "Source.h"
#include "Observer.h"
#include "Entity.h"
#include "Vector2.h"

class Attack : public Entity, Observer
{
private:
	int orbitRadius;
	int curPosIndex;

	int damageAmount;

	double moveCooldownInSeconds;
	Source<double> timeUntilNextMove;

	const Entity* target;

	Vector2<int> CalculatePosition();

	void OnNotify(const Entity* entity, Event event);
	void Move();
public:
	Attack(Entity* target, int orbitRadius, double moveCooldown, int damageAmount);
	void Update(double deltaTime);
};