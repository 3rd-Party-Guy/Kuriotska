#include "Observable.h"

void Observable::AddObserver(Observer* observer) {
	observers.push_back(observer);
}

void Observable::RemoveObserver(Observer* observer) {
	observers.remove(observer);
}

void Observable::Notify(const Entity* entity, Event event) {
	for (Observer* observer : observers) {
		observer->OnNotify(entity, event);
	}
}