#pragma once
#include "RenderTexture.h"


/*NOTE: TODO:
	Menu should have its own loop to pause the game 
*/
enum MenuOptions
{
	RESUME,
	OPTIONS,
	EXIT,
	RESUME_SELECTED,
	OPTIONS_SELECTED,
	EXIT_SELECTED,
	TOTAL
};

class MenuButton {
public:
	void render(SDL_Renderer* renderer, RenderTexture* texture, SDL_Rect* clip);
	void setPosition(int x, int y);
	int getButtonHeight();
	int getButtonWidth();
private:
	SDL_Point position;
	int menuButtonHeight = 160;
	int menuButtonWidth = 204;
};
class Menu {

public:
	bool init(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	bool handleEvents(SDL_Event* event, SDL_Renderer* renderer);
	bool menuLoop(SDL_Event* event, SDL_Renderer* renderer);
private:
	SDL_Rect MenuButtonViewPort[TOTAL];
	MenuButton buttons[TOTAL];
	RenderTexture menuTexture;
	bool shouldRender = false;
};