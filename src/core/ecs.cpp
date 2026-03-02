#include "ecs.h"

void ecs::addEntity(std::shared_ptr<entity> e) {
    onStart.addListener([e]() { e->start(); });
    onUpdate.addListener([e]() { e->update(); });
    onDraw.addListener([e]() { e->draw(); });
    onCleanup.addListener([e]() { e->cleanup(); });
}

void ecs::removeEntity(std::shared_ptr<entity> e) {

}

void ecs::start() {
    onStart.notify();
}

void ecs::update() {
    onUpdate.notify();
}

void ecs::draw() {
    onDraw.notify();
}

void ecs::cleanup() {
    onCleanup.notify();
}
