#include "Source.h"
#include "Event.h"

Source::Source(int amount, int min, int max, Entity* owner, Event eventOnEmpty, Event eventOnFull) :
	amount(amount), min(min), max(max), owner(owner), eventOnEmpty(eventOnEmpty), eventOnFull(eventOnFull) {
	isEmpty = (amount <= 0);
}

void Source::Increase(unsigned a) {
	amount += a;

	if (amount >= max) {
		amount = max;
		Notify(owner, eventOnFull);
	}
}

void Source::Decrease(unsigned a) {
	amount -= a;

	if (amount <= min) {
		amount = min;
		Notify(owner, eventOnEmpty);
	}
}

int Source::GetAmount() const {
	return amount;
}