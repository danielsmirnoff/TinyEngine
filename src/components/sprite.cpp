#include "components/sprite.h"

void sprite::start() {

}

void sprite::update() {

}

void sprite::draw() {
	//Draw
	SDL_RenderTexture(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);
}

void sprite::cleanup() {
    SDL_DestroyTexture(texture);
}

void sprite::setTexture(char* texturePath) {
	if(!renderer) {
		SDL_Log("Renderer is null");
		return;
	}
    //Create surface from file
    char* path;
	SDL_Surface* surface = NULL;
	SDL_asprintf(&path, texturePath, SDL_GetBasePath());
	surface = SDL_LoadPNG(path);
	if (!surface) {
		SDL_Log("Couldnt load png");
		return;
	}
	SDL_free(path);

    //Create texture from surface
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_Log("Couldnt create texture");
		return;
	}

    //Free surface
	SDL_DestroySurface(surface);

    rect.x = 0;
	rect.y = 0;
	rect.w = surface->w;
	rect.h = surface->h;
    SDL_Log("Created Texture! Width: %d Height: %d", surface->w, surface->h);
}