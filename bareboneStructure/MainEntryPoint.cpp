#include <stdio.h>
#include "Includes\Introduction.h"
#include "Includes\Dot.h"


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
RenderTexture dotTexture;
const int screenWidth = 640;
const int screenHeight = 480;
bool init();
void close();
int MainGameLoop();

int main(int argc, char* argv[]) {
	int ret = MainGameLoop();
	return ret;
}

int MainGameLoop() {
	if (!init()) {
		printf("init() Failed\n");
		return -1;
	}
	// Declare Components
	Introduction intro;
	Dot dot;

	// Runs Introduction
	intro.Run(gRenderer);

	bool quit = false;
	SDL_Event eventQ;

	while (!quit) {
		while (SDL_PollEvent(&eventQ) != 0) {
			if (eventQ.type == SDL_QUIT) {
				quit = true;
			}
			// Handles component events       
			dot.handleEvent(&eventQ);
		}
		// Clears the screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		// Update components

		dot.move(screenWidth, screenHeight);
		dot.render(&dotTexture, gRenderer);

		// Update the screen
		SDL_RenderPresent(gRenderer);
	}

	return 0;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Init() Failed\n");
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: SetHint Failed\n");
	}

	gWindow = SDL_CreateWindow(
		"Simple Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!gWindow) {
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!gRenderer) return false;

	if (!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) {
		printf("IMG_Init() Failed\n");
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Mix_OpenAudio() Failed\n");
		return false;
	}

	dotTexture.loadTexture(gRenderer, "Data/dot.bmp");
	return true;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
