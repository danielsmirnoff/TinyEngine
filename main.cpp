#include "main.h"
SDL_Renderer* renderer = nullptr;

entity e;

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		return 1;
	}

	// Create window
	int width = 960;
	int height = 540;
	window = SDL_CreateWindow("Tiny Engine", width, height, 0);
	if (!window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
		cleanup();
		return 1;
	}
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("Couldnt create renderer %s", SDL_GetError());
		cleanup();
		return 0;
	}
	SDL_SetRenderLogicalPresentation(renderer, 960, 540, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	//Call start
	awake();
	start();

	// Start game loop
	bool running = true;
	while (running)
	{
		SDL_Event event{ 0 };
		while (SDL_PollEvent(&event))
		{
			switch (event.type) {
				case SDL_EVENT_QUIT:
				{
					running = false;
					break;
				}
			}
		}
		//Update and draw
		update();
		draw();
	}
	cleanup();
	return 0;
}

void awake() {
	g_ecs.addEntity(std::make_shared<entity>(e));
}

void start() {
	g_ecs.start();
}

void update() {
	g_ecs.update();
}

void draw() {
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	//Draw entities
	g_ecs.draw();
}

void cleanup() {
	g_ecs.cleanup();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
