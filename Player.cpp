#include <curses.h>

#include <chrono>
#include <string>

#include "Player.h"
#include "EnemyManager.h"
#include "Misc.h"
#include "Debugger.h"

void Player::ManageAir() {
	while (IsAlive()) {
		(isInWater) ? air.Decrease(1) : air.Increase(1);

		std::chrono::milliseconds sleepDuration(waterAirTime);
		std::this_thread::sleep_for(sleepDuration);
	}
}

void Player::SetPositionRel(int xVel, int yVel) {
	Vector2<int> newPos = GetPosition() + Vector2<int>(xVel, yVel);
	
	const MapNode* newNode = map->GetNode(newPos);
	if (newNode == nullptr)	// out of bounds
		return;
	isInWater = (newNode->GetType() == MapNodeType::Water);

	Entity::SetPositionRel(xVel, yVel);
	EnemyManager::instance().DamageEnemyAtPos(GetPosition(), 1);
}

const int Player::GetLevel() const {
	return level;
}

const int Player::GetAir() const {
	return air.GetAmount();
}

void Player::Damage(int damage) {
	flash();
	Actor::Damage(damage);
}

void Player::GetKill() {
	--killsUntilNextLevel;

	// Level Up
	if (killsUntilNextLevel <= 0) {
		level++;
		health.Increase(Misc::RandomInRange(1, 2));

		double curAttacksAmount = attacksAmount;
		attacksAmount = pow(attacksAmount, 1.125);
		
		std::string debugInfo = std::to_string(curAttacksAmount) + ", " +
			std::to_string(attacksAmount);

		Debugger::instance().ShowInfo(debugInfo);

		for (int i = curAttacksAmount; i < attacksAmount; ++i)
			AddAttack();
		
		killsUntilNextLevel = level * 2;
	}
}

const std::unordered_set<std::unique_ptr<Attack>>& Player::GetAttacks() const {
	return attacks;
}

void Player::AddAttack() {
	int orbitRadius = Misc::RandomInRange(1, 10);
	int moveCooldown = Misc::RandomInRange(10, 250);
	int damageAmount = Misc::RandomInRange(4, 4);

	attacks.insert(std::make_unique<Attack>
		(this, orbitRadius, moveCooldown, damageAmount)
	);
}

void Player::OnNotify(const Entity* entity, Event event) {
	switch (event) {
	case Event::HEALTH_EMPTY:
	case Event::AIR_EMPTY:
		OnDeath();
		break;
	default:
		break;
	}
}

Player::Player(Map* map, int x, int y, int startAttackAmount) : Actor(x, y, 10, true, map), air(10, 0, 10, this, Event::AIR_EMPTY, Event::AIR_FULL),
	isInWater(false), airThread(&Player::ManageAir, this), level(1), killsUntilNextLevel(2) {
	air.AddObserver(this);
	attacksAmount = startAttackAmount;
	for (int i = 0; i < attacksAmount; ++i)
		AddAttack();
}

Player::~Player() {
	if (airThread.joinable())
		airThread.join();
}