#include <curses.h>

#include <chrono>
#include <string>

#include "Misc.h"
#include "Player.h"

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
}

int Player::GetAir() const {
	return air.GetAmount();
}

void Player::Damage(int damage) {
	flash();
	Actor::Damage(damage);
}

const std::vector<std::unique_ptr<Attack>>& Player::GetAttacks() const {
	return attacks;
}

void Player::AddAttack() {
	int orbitRadius = Misc::RandomInRange(1, 10);
	int moveCooldown = Misc::RandomInRange(50, 1000);
	int damageAmount = Misc::RandomInRange(4, 4);

	attacks.push_back(std::make_unique<Attack>
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

Player::Player(Map* map, int x, int y) : Actor(x, y, 10, true, map), air(10, 0, 10, this, Event::AIR_EMPTY, Event::AIR_FULL),
	isInWater(false), airThread(&Player::ManageAir, this) {
	air.AddObserver(this);
	AddAttack();
	AddAttack();
	AddAttack();
	AddAttack();
	AddAttack();
	AddAttack();
}

Player::~Player() {
	if (airThread.joinable())
		airThread.join();
}