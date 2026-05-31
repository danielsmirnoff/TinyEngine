#pragma once
#include <SDL3/SDL.h>
#include "ecs.h"
using namespace std;

static SDL_Window *window = nullptr;
extern SDL_Renderer* renderer; 
static ecs g_ecs;

void awake();
void start();
void update();
void draw();
void cleanup();

