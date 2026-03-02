#pragma once
#include <SDL3/SDL.h>

class component {
    public:
    component() = default;
    ~component() = default;
    virtual void start();
    virtual void update();
    virtual void draw();
    virtual void cleanup();
};