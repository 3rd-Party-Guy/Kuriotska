#pragma once

#include <thread>
#include <memory>
#include <unordered_set>

#include "Actor.h"
#include "Observer.h"
#include "Event.h"
#include "Map.h"
#include "Source.h"
#include "Attack.h"

class Player : public Actor
{
private:
	bool isInWater;
	Source<unsigned short> air;
	unsigned short waterAirTime = 500;															// In Milliseconds
	std::thread airThread;
	
	std::unordered_set<std::unique_ptr<Attack>> attacks;
	
	void ManageAir();
	virtual void OnNotify(const Entity* entity, Event event) override;
	void SetPositionRel(int xVel, int yVel) override;
	
	int level;
	int killsUntilNextLevel;
	int attacksAmount;

public:
	const int GetLevel() const;
	const int GetAir() const;
	void Damage(int damage) override;
	const std::unordered_set<std::unique_ptr<Attack>>& GetAttacks() const;
	
	void AddAttack();
	void UpdateAttacks(double deltaTime);
	void GetKill();

	Player(Map* map, int x, int y, int startAttackAmount);
	~Player();
};