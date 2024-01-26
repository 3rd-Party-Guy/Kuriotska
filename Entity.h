#pragma once

#include "Vector2.h"

class Entity
{
private:
	Vector2<int> position;
protected:
	bool isPlayer;
public:
	Entity(int x, int y);
	Entity(Vector2<int> position);
	Vector2<int> GetPosition() const;
	virtual void SetPositionAbs(int newX, int newY);
	virtual void SetPositionAbs(Vector2<int> newPos);
	virtual void SetPositionRel(int xVel, int yVel);
	virtual void SetPositionRel(Vector2<int> velocity);
};