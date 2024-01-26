#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
	int attackDistance;
	bool IsPlayerWithinDistance() const;
};