#include <stdio.h>
#include "Introduction.h"


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
const int screenWidth = 640;
const int screenHeight = 480;
bool init();
void close();

int main(int argc, char* argv[]) {
	if (!init()) {
                printf("init() Failed\n");
		return -1;
	}
	Introduction ab;
        ab.Run(gRenderer);


        bool quit = false;
        SDL_Event eventQ;

        while(!quit){
                while(SDL_PollEvent(&eventQ) != 0){
                        if(eventQ.type == SDL_QUIT){
                                quit = true
                        }
                        //handles events       

                }
                //handles rendering

        }

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
        if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0){
                printf("Mix_OpenAudio() Failed\n");
                return false;
        }
	return true;
}

void close(){
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
        gRenderer = NULL;

        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
}
