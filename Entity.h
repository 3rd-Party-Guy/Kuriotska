#pragma once

#include "Vector2.h"

class Entity
{
private:
	Vector2<int> position;
public:
	Entity();
	Entity(Vector2<int> position);
	Vector2<int> GetPosition() const;
	void SetPositionAbs(int newX, int newY);
	void SetPositionAbs(Vector2<int> newPos);
	void SetPositionRel(int xVel, int yVel);
};