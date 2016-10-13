#include "Introduction.h"

bool Introduction::Run(SDL_Renderer* renderer) {
	/*if (!init()) {
	printf("init() Failed\n");
	return false;
	}*/
	if (!loadMedia(renderer, "Data/logo.png")) {
		printf("[Introduction]loadMedia() Failed\n");
		return false;
	}

	SDL_Event event;
	Uint8 alpha = 0;
	bool quit = false;

	while (!quit) {
		//fade in
		while (alpha<255) {
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(renderer);
			SDL_SetTextureAlphaMod(introTexture, alpha);
			SDL_RenderCopy(renderer, introTexture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
			alpha++;
		}
		//fade out
		while (alpha>0) {
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(renderer);
			SDL_SetTextureAlphaMod(introTexture, alpha);
			SDL_RenderCopy(renderer, introTexture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_Delay(5);
			alpha--;
		}
		quit = true;
		SDL_Delay(50);
	}
	free();
	return true;
}


Introduction::Introduction() {
	introTexture = NULL;
	textureWidth = 0;
	textureHeight = 0;
}
Introduction::~Introduction() {
	free();
}

bool Introduction::loadMedia(SDL_Renderer* renderer, std::string path) {
	free();
	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(path.c_str());
	if (!tempSurface) return false;

	//SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

	introTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!introTexture) { return false; }

	textureWidth = tempSurface->w;
	textureHeight = tempSurface->h;

	SDL_FreeSurface(tempSurface);
	return true;
}
/*
void abTexture::setBlendMode(SDL_BlendMode blending) {
SDL_SetTextureBlendMode(texture, blending);
}
*/
void Introduction::free() {
	if (!introTexture) {
		SDL_DestroyTexture(introTexture);
		introTexture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}