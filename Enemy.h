#pragma once

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
private:
	static size_t nextID;

	size_t ID;
	int attackDistance;
	bool isChasing;
	bool IsPlayerWithinDistance() const;
	const Entity* player;

public:
	const size_t GetID() const;
	Enemy(Vector2<int> position, int attackDistance, Entity* player);
	const bool operator==(const Enemy& other) const;
};