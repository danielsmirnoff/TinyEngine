#pragma once
using namespace std;
#include <memory>
#include <SDL3/SDL.h>
#include "utils/map.h"
#include "components/component.h"

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
	private:
		map<std::shared_ptr<component>> components;

};