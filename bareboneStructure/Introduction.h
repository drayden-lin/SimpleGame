#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <stdio.h>

#define INTRO_TEXTURE "Data/logo.png"
#define INTRO_MUSIC "Data/Sounds/intro.wav"

class Introduction {
public:
	Introduction();
	~Introduction();
	bool Run(SDL_Renderer* renderer);
	bool loadTexture(SDL_Renderer* renderer, std::string path);
        bool loadMusic(std::string path);
	void freeTexture();
        void freeMusic();

private:
	int textureWidth;
	int textureHeight;
	SDL_Texture* introTexture;
        Mix_Music* introMusic;
};
