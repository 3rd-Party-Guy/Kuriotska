#include <chrono>
#include <cmath>

#include "Attack.h"
#include "EnemyManager.h"

Attack::Attack(Entity* newTarget, int orbitRadius, int moveCooldown, int damageAmount) : target(newTarget), orbitRadius(orbitRadius),
curPosIndex(1), Entity(0, 0), moveCooldown(moveCooldown), damageAmount(damageAmount) {
	SetPositionAbs(newTarget->GetPosition());
	updateThread = std::thread(&Attack::Update, this);
}

Vector2<int> Attack::CalculatePosition() {
	int newX = orbitRadius * cos(curPosIndex) + target->GetPosition().GetX();
	int newY = orbitRadius * sin(curPosIndex) + target->GetPosition().GetY();
	
	++curPosIndex %= 360;

	return Vector2<int>(newX , newY);
}

void Attack::Update() {
	while (true) {
		SetPositionAbs(CalculatePosition());
		EnemyManager::instance().DamageEnemyAtPos(GetPosition(), damageAmount);

		std::this_thread::sleep_for(moveCooldown);
	}
}
