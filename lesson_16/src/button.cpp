#include "../headers/button.hpp"
#include "../headers/texture.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>

LButton::LButton(SDL_Renderer* newRenderer)
{
	mPosition.x = 0;
	mPosition.y = 0;
	gRenderer = newRenderer;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPos(int x, int y) {
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event *e) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		if (x < mPosition.x) {
			inside = false;
		}
		else if (x > mPosition.x + BUTTON_WIDTH) {
			inside = false;
		}
		else if (y < mPosition.y) {
			inside = false;
		}
		else if (y > mPosition.y + BUTTON_HEIGHT) {
			inside = false;
		}

		if (!inside) {
			mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
		}
		else {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}

		}
	}
}

void LButton::render(SDL_Rect gSpriteClips[]) {
	gTexture->render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}