#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "event.h"
#include "entity.h"

class ecs {
	public:
		 ecs() = default;
		 ~ecs() = default;
		 void addEntity(std::shared_ptr<entity> e);
		 void removeEntity(std::shared_ptr<entity> e);
		 void start();
		 void update();
		 void draw();
		 void cleanup();
	protected:
		event onStart;
		event onUpdate;
		event onDraw;
		event onCleanup;
	private:
		std::shared_ptr<entity> entities;
};
