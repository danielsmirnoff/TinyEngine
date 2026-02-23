#include <SDL3/SDL.h>
#include "TinyEngine.h"

using namespace std;

void cleanup(SDL_Window *window);

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		return 1;
	}

	// Create window
	int width = 960;
	int height = 540;
	SDL_Window* win = SDL_CreateWindow("Tiny Engine", width, height, 0);
	if (!win) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
		cleanup(win);
		return 1;
	}

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
	}
	cleanup(win);
	return 0;
}

void cleanup(SDL_Window *window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
