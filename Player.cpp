#include <chrono>
#include <string>

#include "Debugger.h"
#include "Player.h"

void Player::OnNotify(const Entity* entity, Event event) {
	switch (event) {
	case Event::AIR_EMPTY:
	case Event::HEALTH_EMPTY:
		isAlive = false;
		Debugger::instance().ShowInfo("\nthis gets called");
		break;
	default:
		break;
	}
}

bool Player::IsAlive() const {
	return isAlive;
}

void Player::ManageAir() {
	using namespace std::chrono_literals;

	while (isAlive) {
		(isInWater) ? air.Decrease(1) : air.Increase(1);
		std::this_thread::sleep_for(2s);
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

int Player::GetHealth() const {
	return health.GetAmount();
}

int Player::GetAir() const {
	return air.GetAmount();
}

Player::Player(const Map* map, int x, int y) : map(map), health(10, 0, 10, this, Event::HEALTH_EMPTY, Event::HEALTH_FULL), air(10, 0, 10, this, Event::AIR_EMPTY, Event::AIR_FULL),
	isInWater(false), isAlive(true), airThread(&Player::ManageAir, this) {
	air.AddObserver(this);
	health.AddObserver(this);
	isPlayer = true;
	SetPositionAbs(x, y);
}

Player::~Player() {
	if (airThread.joinable())
		airThread.join();
}