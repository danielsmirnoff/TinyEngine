#pragma once
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include "engine/subsystems/core/subsystemregistry.h"

//static entt::registry ecs;

class Engine {
    public:
        static inline GLFWwindow* window = nullptr;
        int Run();

        void Start();
        void Update();
        void Render();
        void Cleanup();
    private:
};