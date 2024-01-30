#pragma once

#include <thread>

#include "Actor.h"
#include "Observer.h"
#include "Event.h"
#include "Map.h"
#include "Source.h"

class Player : public Actor
{
private:
	bool isInWater;
	Source air;
	unsigned short waterAirTime = 500;															// In Milliseconds
	std::thread airThread;
	
	void ManageAir();

	virtual void SetPositionRel(int xVel, int yVel) override;

public:
	int GetAir() const;
	void Damage(int damage) override;

	Player(Map* map, int x, int y);
	~Player();
};