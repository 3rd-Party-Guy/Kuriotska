#pragma once

#include <list>

#include "Observer.h"

class Observable
{
private:
	std::list<Observer*> observers;
protected:
	void Notify(const Entity* entity, Event event);
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
};