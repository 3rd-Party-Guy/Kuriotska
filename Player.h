#pragma once

#include <thread>

#include "Entity.h"
#include "Observer.h"
#include "Event.h"
#include "Map.h"
#include "Source.h"

class Player : public Entity, Observer
{
private:
	bool isAlive;
	Source health;
	Source air;
	const Map* map;
	virtual void OnNotify(const Entity* entity, Event event);

	std::thread airThread;
	bool isInWater;
	unsigned short waterAirTime = 500;															// In Milliseconds
	void ManageAir();
public:
	bool IsAlive() const;
	void SetPositionRel(int xVel, int yVel) override;
	int GetHealth() const;
	int GetAir() const;
	Player(const Map* map, int x, int y);
	~Player();
};