#include "Includes\Dot.h"

Dot::Dot() {
	xVelocity = 0;
	yVelocity = 0;
	xPosition = 0;
	yPosition = 0;
	velocityInterval = 10;
}

void Dot::handleEvent(SDL_Event* event) {
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
		switch (event->key.keysym.sym) {
		case SDLK_UP:
			yVelocity -= velocityInterval;
			break;
		case SDLK_DOWN:
			yVelocity += velocityInterval;
			break;
		case SDLK_LEFT:
			xVelocity -= velocityInterval;
			break;
		case SDLK_RIGHT:
			xVelocity += velocityInterval;
			break;
		}
	}
	else if (event->type == SDL_KEYUP && event->key.repeat == 0) {
		switch (event->key.keysym.sym) {
		case SDLK_UP:
			yVelocity += velocityInterval;
			break;
		case SDLK_DOWN:
			yVelocity -= velocityInterval;
			break;
		case SDLK_LEFT:
			xVelocity += velocityInterval;
			break;
		case SDLK_RIGHT:
			xVelocity -= velocityInterval;
			break;
		}
	}
}

void Dot::move(int maxWidth, int maxHeight) {
	xPosition += xVelocity;
	if (xPosition<0 || xPosition + dotWidth > maxWidth)
		xPosition -= xVelocity;

	yPosition += yVelocity;
	if (yPosition < 0 || yPosition + dotHeight > maxHeight)
		yPosition -= yVelocity;
}

void Dot::render(RenderTexture* texture, SDL_Renderer* renderer) {
	texture->render(renderer, xPosition, yPosition);
}

void Dot::setVelocityInterval(int v) {
	velocityInterval = v;
}
