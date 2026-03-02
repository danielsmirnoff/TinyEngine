#pragma once
#include <SDL3/SDL.h>
#include "../../main.h"
#include "component.h"

class sprite : component {
    public:
    sprite() = default;
    ~sprite() = default;
    void start() override;
    void update() override;
    void draw() override;
    void cleanup() override;
    private:
    SDL_Texture* texture;
    SDL_FRect rect;
    void setTexture(char* texturePath);
};