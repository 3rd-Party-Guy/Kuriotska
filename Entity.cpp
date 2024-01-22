#include "Entity.h"

Entity::Entity(Vector2<int> position) : position(position) { }
Entity::Entity() : position(0, 0) { }

Vector2<int> Entity::GetPosition() const {
	return position;
}

void Entity::SetPositionAbs(int newX, int newY) {
	position.Set(newX, newY);
}

void Entity::SetPositionRel(int xVel, int yVel) {
	position.Set(position.GetX() + xVel, position.GetY() + yVel);
}