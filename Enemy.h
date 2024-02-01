#pragma once

#include "Actor.h"
#include "Player.h"
#include "EnemyState.h"
#include "Source.h"
#include "Event.h"

class Enemy : public Actor
{
private:
	static int nextID;

	int ID;
	int chaseDistance;

	Player* player;
	
	EnemyState curState;
	
	void Act();
	void CheckState();
	void TryChasePlayer();
	void OnDeath() override;
public:
	const int GetID() const;
	Enemy(Vector2<int> position, int chaseDistance, Player* player, Map* map);
	const bool operator==(const Enemy& other) const;
	void Update();
	static int GetNextID();
};