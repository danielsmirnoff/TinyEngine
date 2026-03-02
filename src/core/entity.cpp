#include "entity.h"
#include "../../main.h"

void entity::start() {
}

void entity::update() {

}

void entity::draw() {

}

void entity::cleanup() {
}

void entity::addComponent(std::shared_ptr<component> c) {
	components.add(c);
}

void entity::removeComponent(int index) {
	components.remove(index);
}