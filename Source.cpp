#include "Source.h"
#include "Event.h"

template <class T>
Source<T>::Source(T amount, T min, T max, Entity* owner, Event eventOnEmpty, Event eventOnFull) :
	amount(amount), min(min), max(max), owner(owner), eventOnEmpty(eventOnEmpty), eventOnFull(eventOnFull) {
	isEmpty = (amount <= 0);
}

template <class T>
void Source<T>::Increase(T a) {
	amount += a;

	if (amount >= max) {
		amount = max;
		Notify(owner, eventOnFull);
	}
}

template <class T>
void Source<T>::Decrease(T a) {
	amount -= a;

	if (amount <= min) {
		amount = min;
		Notify(owner, eventOnEmpty);
	}
}

template <class T>
T Source<T>::GetAmount() const {
	return amount;
}

template class Source<int>;
template class Source<double>;
template class Source<unsigned short>;