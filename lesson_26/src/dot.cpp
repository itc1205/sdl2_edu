#include "../headers/dot.hpp"
#include "../headers/game_class.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

Dot::Dot() {
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event &e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
		case SDLK_UP: mVelY -= DOT_VEL; break;
		case SDLK_DOWN: mVelY += DOT_VEL; break;
		case SDLK_LEFT: mVelX -= DOT_VEL; break;
		case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: mVelY += DOT_VEL; break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: mVelX -= DOT_VEL; break; 
		}
	}
}

void Dot::move() {
	if (!(mPosX + mVelX + DOT_WIDTH > SCREEN_WIDTH ||
		  mPosX + mVelX < 0)) {
		mPosX += mVelX;
	}
	if (!(mPosY + mVelY + DOT_HEIGHT > SCREEN_HEIGHT ||
		  mPosY + mVelY < 0)) {
		mPosY += mVelY;
	}
}

void Dot::setTexture(LTexture *newTexture) {
	gTexture = newTexture;
}

void Dot::render() {
	gTexture->render(mPosX, mPosY);
}