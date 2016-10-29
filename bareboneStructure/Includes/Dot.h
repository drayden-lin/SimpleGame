#pragma once
#include "RenderTexture.h"

class Dot {
public:
	Dot();
	void handleEvent(SDL_Event* event);
	void move(int maxWidth, int maxHeight);
	void render(RenderTexture* texture, SDL_Renderer* renderer);

	void setVelocityInterval(int v);
private:
	int xVelocity, yVelocity;
	int xPosition, yPosition;
	int velocityInterval;
	int dotWidth = 20;
	int dotHeight = 20;

};