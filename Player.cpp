#include <chrono>
#include <string>

#include "Debugger.h"
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

Player::Player(Map* map, int x, int y) : Actor(x, y, 10, true, map), air(10, 0, 10, this, Event::AIR_EMPTY, Event::AIR_FULL),
	isInWater(false), airThread(&Player::ManageAir, this) {
}

Player::~Player() {
	if (airThread.joinable())
		airThread.join();
}