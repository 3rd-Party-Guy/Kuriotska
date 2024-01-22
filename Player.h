#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	int hp;
	const int startHP = 100;

public:
	void MoveAbs(int x, int y);
	void MoveRel(int xVel, int yVel);
	Player();
};