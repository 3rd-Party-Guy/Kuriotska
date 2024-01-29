#pragma once

#include "Entity.h"
#include "Player.h"
#include "EnemyState.h"
#include "Source.h"
#include "Event.h"

class Enemy : public Entity
{
private:
	static size_t nextID;

	size_t ID;
	int chaseDistance;
	Player* player;
	EnemyState curState;
	Source health;
	
	void Act();
	void CheckState();

	void OnHealthFull();
	void OnHealthEmpty();

public:
	const size_t GetID() const;
	Enemy(Vector2<int> position, int chaseDistance, Player* player);
	const bool operator==(const Enemy& other) const;
	void Update();
};