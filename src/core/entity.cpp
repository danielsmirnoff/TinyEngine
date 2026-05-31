#include "entity.h"
#include "main.h"

void entity::start() {
	for (auto& [index, component] : components)
	{
		component->start();
	}
}

void entity::update() {
	for (auto& [index, component] : components)
	{
		component->update();
	}
}

void entity::draw() {
	for (auto& [index, component] : components)
	{
		component->draw();
	}
}

void entity::cleanup() {
	for (auto& [index, component] : components)
	{
		component->cleanup();
	}
}

void entity::addComponent(std::shared_ptr<component> c) {
	components.add(c);
	SDL_Log("Added component");
}

void entity::removeComponent(int index) {
	components.remove(index);
}