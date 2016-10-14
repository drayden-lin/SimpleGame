#include "Introduction.h"

bool Introduction::Run(SDL_Renderer* renderer) {

	if (!loadTexture(renderer, INTRO_TEXTURE)) {
		printf("[Introduction]loadMedia() Failed\n");
		return false;
	}

        if (!loadMusic(INTRO_MUSIC)){
                printf("[Introduction]loadMusic() Failed\n");
                return false;
        }

	Uint8 alpha = 0;

	//fade in
        Mix_PlayMusic( introMusic, -1 );
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
	SDL_Delay(50);

	freeTexture();
        freeMusic();
	return true;
}


Introduction::Introduction() {
	introTexture = NULL;
	textureWidth = 0;
	textureHeight = 0;
}
Introduction::~Introduction() {
	freeTexture();
        freeMusic();
}

bool Introduction::loadTexture(SDL_Renderer* renderer, std::string path) {
	freeTexture();
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
void Introduction::freeTexture() {
	if (!introTexture) {
		SDL_DestroyTexture(introTexture);
		introTexture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}

void Introduction::freeMusic() {
        if (!introMusic) {
                Mix_FreeMusic(introMusic);
                introMusic = NULL;
        }
}

bool Introduction::loadMusic(std::string path){
        freeMusic();
        introMusic = Mix_LoadMUS(path.c_str());
        return introMusic? true:false;

}
