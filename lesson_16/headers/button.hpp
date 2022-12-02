#ifndef _button_h_
#define _button_h_ value

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include "texture.hpp"

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};


class LButton {
public:
	LButton(SDL_Renderer* newRenderer);
	~LButton();

	void setPos(int x, int y);
	void handleEvent(SDL_Event* e);

	void render(SDL_Rect gSpriteClips[]);

private:
	SDL_Renderer* gRenderer;
	LTexture* gTexture;
	SDL_Point mPosition;
	LButtonSprite mCurrentSprite;

};

#endif