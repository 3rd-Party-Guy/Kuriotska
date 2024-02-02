#include <chrono>
#include <cmath>

#include "Attack.h"
#include "EnemyManager.h"

Attack::Attack(Entity* newTarget, int orbitRadius, double moveCooldown, int damageAmount) : target(newTarget), orbitRadius(orbitRadius),
curPosIndex(1), Entity(0, 0), moveCooldownInSeconds(moveCooldown), damageAmount(damageAmount),
timeUntilNextMove(moveCooldown, 0, moveCooldown, this, Event::SOURCE_EMPTY, Event::SOURCE_FULL) {
	SetPositionAbs(newTarget->GetPosition());
	timeUntilNextMove.AddObserver(this);
}

Vector2<int> Attack::CalculatePosition() {
	int newX = std::lround(orbitRadius * cos(curPosIndex) + target->GetPosition().GetX());
	int newY = std::lround(orbitRadius * sin(curPosIndex) + target->GetPosition().GetY());
	
	++curPosIndex %= 360;

	return Vector2<int>(newX , newY);
}

void Attack::Move() {
	SetPositionAbs(CalculatePosition());
	EnemyManager::instance().DamageEnemyAtPos(GetPosition(), damageAmount);
	timeUntilNextMove.Increase(moveCooldownInSeconds);
}

void Attack::OnNotify(const Entity* entity, Event event) {
	switch (event) {
	case Event::SOURCE_EMPTY:
		Move();
		break;
	default:
		break;
	}
}

void Attack::Update(double deltaTime) {
	timeUntilNextMove.Decrease(deltaTime);
}
