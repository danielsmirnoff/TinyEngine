#include "event.h"

void event::notify() {
	for (const auto& pair : listeners)
	{
		pair.second();
	}
}

int event::addListener(std::function<void()> callback) {
	listeners[nextId] = callback;
	return nextId++;
}

void event::removeListener(int id) {
	listeners.erase(id);
}

void event::removeAllListeners() {
	listeners.clear();
	nextId = 0;
}