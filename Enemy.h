#pragma once

#include "Entity.h"
#include "Player.h"
#include "EnemyState.h"

class Enemy : public Entity
{
private:
	static size_t nextID;

	size_t ID;
	int chaseDistance;
	Player* player;
	EnemyState curState;
	
	void Act();
	void CheckState();

public:
	const size_t GetID() const;
	Enemy();
	Enemy(Vector2<int> position, int chaseDistance, Player* player);
	const bool operator==(const Enemy& other) const;
	void Update();
};