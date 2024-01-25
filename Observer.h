#pragma once

#include "Entity.h"
#include "Event.h"

class Observer
{
public:
	virtual void OnNotify(const Entity* entity, Event event) = 0;
};