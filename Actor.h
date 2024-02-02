#pragma once

#include "Entity.h"
#include "Map.h"
#include "Observer.h"
#include "Source.h"

class Actor : public Entity, public Observer
{
private:
	bool isAlive;
	bool hasPriority;															// means can walk on non-free nodes

	virtual void OnNotify(const Entity* entity, Event event);

protected:
	Source<unsigned short> health;
	Map* map;

public:
	Actor(int x, int y, int maxHealth, bool hasPriority, Map* map);
	Actor(Vector2<int> position, int maxHealth, bool hasPriority, Map* map);

	virtual void SetPositionAbs(int newX, int newY) override;
	virtual void SetPositionAbs(Vector2<int> newPos) override;
	virtual void SetPositionRel(int xVel, int yVel) override;
	virtual void SetPositionRel(Vector2<int> velocity) override;

	virtual void Damage(int amount);

	int GetHealth() const;
	bool IsAlive() const;
	virtual void OnDeath();
};