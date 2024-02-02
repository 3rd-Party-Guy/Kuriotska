#pragma once

#include "Observable.h"

template <class T>
class Source : public Observable
{
private:
	T amount;
	const T max;
	const T min;
	bool isEmpty;
	const Entity* owner;
	Event eventOnEmpty;
	Event eventOnFull;
public:
	void Increase(T a);
	void Decrease(T a);
	Source(T amount, T min, T max, Entity* owner, Event eventOnEmpty, Event eventOnFull);
	T GetAmount() const;
};