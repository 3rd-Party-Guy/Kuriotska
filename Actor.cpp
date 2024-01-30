#include "Actor.h"

Actor::Actor(int x, int y, int maxHealth, bool hasPriority, Map* map) : Entity(x, y), hasPriority(hasPriority),
	map(map), health(maxHealth, 0, maxHealth, this, Event::HEALTH_EMPTY, Event::HEALTH_FULL), isAlive(true) {
	health.AddObserver(this);
}

Actor::Actor(Vector2<int> position, int maxHealth, bool hasPriority, Map* map) :
	Actor(position.GetX(), position.GetY(), maxHealth, hasPriority, map) { };

void Actor::SetPositionAbs(int newX, int newY) {
	map->SetNodeIsFree(GetPosition(), true);
	if (!map->GetNodeIsFree(newX, newY) && !hasPriority) return;

	map->SetNodeIsFree(newX, newY, false);
	Entity::SetPositionAbs(newX, newY);
}

void Actor::SetPositionAbs(Vector2<int> newPos) {
	SetPositionAbs(newPos.GetX(), newPos.GetY());
}

void Actor::SetPositionRel(int xVel, int yVel) {
	const Vector2<int> curPos = GetPosition();
	SetPositionAbs(curPos.GetX() + xVel, curPos.GetY() + yVel);
}

void Actor::SetPositionRel(Vector2<int> velocity) {
	SetPositionAbs(GetPosition() + velocity);
}

void Actor::Damage(int amount) {
	health.Decrease(amount);
}

int Actor::GetHealth() const {
	return health.GetAmount();
}

void Actor::OnNotify(const Entity* entity, Event event) {
	switch (event) {
	case Event::HEALTH_EMPTY:
		OnDeath();
		break;
	default:
		break;
	}
}

bool Actor::IsAlive() const {
	return isAlive;
}

void Actor::OnDeath() {
	isAlive = false;
}