#pragma once
using namespace std;
#include <memory>
#include <SDL3/SDL.h>
#include "map.h"
#include "component.h"

class entity {
	public:
		entity() = default;
		~entity() = default;
		void start();
		void update();
		void draw();
		void cleanup();
		void addComponent(std::shared_ptr<component> c);
		void removeComponent(int index);
	protected:
		map<std::shared_ptr<component>> components;

};

#include "map.cpp"