#include "Includes\Menu.h"

bool Menu::init(SDL_Renderer* renderer) {
	bool ret = true;
	if (!menuTexture.loadTexture(renderer, "Data/Menu.png")) {
		printf("Menu Init Failed\n");
		ret = false;
	}

	for (int i = 0; i < TOTAL; i++) {
		MenuButtonViewPort[i].x = 0;
		MenuButtonViewPort[i].y = i * 160;
		MenuButtonViewPort[i].w = buttons[i].getButtonWidth();
		MenuButtonViewPort[i].h = buttons[i].getButtonHeight();
	}

	buttons[0].setPosition(0, 0);
	buttons[1].setPosition(0, 160);
	buttons[2].setPosition(0, 320);
	buttons[3].setPosition(0, 0);
	buttons[4].setPosition(0, 160);
	buttons[5].setPosition(0, 320);

	return ret;
}

// Renders the Menu Texture
void Menu::render(SDL_Renderer* renderer) {
	menuTexture.render(renderer, 0, 0);
}

bool Menu::handleEvents(SDL_Event* event, SDL_Renderer* renderer) {
	if (event->type == SDL_KEYDOWN) {
		// Escape(ESC) is pressed, we enter the menu loop to pause the game 
		// and handle further events from there
		if (event->key.keysym.sym == SDLK_ESCAPE && event->key.repeat == 0) {
			return menuLoop(event, renderer);
		}
	}
}

// Menu Loop to pause the game and handle events during the pause
bool Menu::menuLoop(SDL_Event* event, SDL_Renderer* renderer) {
	bool quitLoop = false;
	int cursorPosition = 0;
	int displayedButtons = 3;

	while (!quitLoop) {
		while (SDL_PollEvent(event) != 0) {
			if (event->type == SDL_QUIT) {
				//quitLoop = true;
				return false;
			}
			if (event->type == SDL_KEYDOWN) {
				switch (event->key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quitLoop = true;
					break;
				case SDLK_UP:
					cursorPosition--;
					if (cursorPosition < 0)
						cursorPosition = 0;
					break;
				case SDLK_DOWN:
					cursorPosition++;
					if (cursorPosition > 2)
						cursorPosition = 2;
					break;
				case SDLK_RETURN:
					if (cursorPosition == 0) {
						quitLoop = true;
					}
					else if (cursorPosition == 1) {
						//do nothing atm
					}
					else if (cursorPosition == 2) {
						return false;
					}
					break;
				//Other Cases
				default:
					break;
				}
			}
		}
		// render menu
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Renders all buttons
		for (int i = 0; i < displayedButtons; i++) {
			buttons[i].render(renderer, &menuTexture, &MenuButtonViewPort[i]);
		}
		//Updates the Currently Selected Button
		buttons[cursorPosition+3].render(renderer, &menuTexture, &MenuButtonViewPort[cursorPosition+3]);

		SDL_RenderPresent(renderer);
	}
}

void MenuButton::render(SDL_Renderer* renderer, RenderTexture* texture, SDL_Rect* clip) {
	texture->render(renderer, position.x, position.y, clip);
}

void MenuButton::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

int MenuButton::getButtonHeight() {
	return menuButtonHeight;
}

int MenuButton::getButtonWidth() {
	return menuButtonWidth;
}