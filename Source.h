#pragma once

#include "Observable.h"

class Source : public Observable
{
private:
	int amount;
	const int max;
	const int min;
	bool isEmpty;
	const Entity* owner;
	Event eventOnEmpty;
	Event eventOnFull;
public:
	void Increase(unsigned a);
	void Decrease(unsigned a);
	Source(int amount, int min, int max, Entity* owner, Event eventOnEmpty, Event eventOnFull);
	int GetAmount() const;
};