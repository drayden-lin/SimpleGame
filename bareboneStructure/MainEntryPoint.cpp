#include <stdio.h>
#include "Introduction.h"


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
const int screenWidth = 640;
const int screenHeight = 480;
bool init();

int main(int argc, char* argv[]) {
	if (!init()) {
		return -1;
	}
	Introduction ab;
	ab.Run(gRenderer);

	return 0;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init() Failed\n");
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: SetHint Failed\n");
	}

	gWindow = SDL_CreateWindow(
		"Alpha Blending",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!gWindow) {
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!gRenderer) return false;

	if (!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) {
		printf("IMG_Init() Failed\n");
		return false;
	}

	return true;
}