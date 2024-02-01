#pragma once

#include <thread>
#include <memory>
#include <vector>

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
	Source air;
	unsigned short waterAirTime = 500;															// In Milliseconds
	std::thread airThread;
	
	std::vector<std::unique_ptr<Attack>> attacks;
	
	void ManageAir();
	virtual void OnNotify(const Entity* entity, Event event) override;
	void SetPositionRel(int xVel, int yVel) override;
	
	int level;
	int killsUntilNextLevel;
	double attacksAmount;

public:
	const int GetLevel() const;
	const int GetAir() const;
	void Damage(int damage) override;
	const std::vector<std::unique_ptr<Attack>>& GetAttacks() const;
	
	void AddAttack();
	void GetKill();

	Player(Map* map, int x, int y, int startAttackAmount);
	~Player();
};