#include "Entity.h"

Entity::Entity(int x, int y) : position(x, y), isPlayer(false) { }
Entity::Entity(Vector2<int> position) : position(position), isPlayer(false) { }

Vector2<int> Entity::GetPosition() const {
	return position;
}

void Entity::SetPositionAbs(int newX, int newY) {
	position.Set(newX, newY);
}

void Entity::SetPositionAbs(Vector2<int> newPos) {
	position.Set(newPos);
}

void Entity::SetPositionRel(int xVel, int yVel) {
	position.Set(position.GetX() + xVel, position.GetY() + yVel);
}

void Entity::SetPositionRel(Vector2<int> velocity) {
	position.Set(position.GetX() + velocity.GetX(), position.GetY() + velocity.GetY());
}