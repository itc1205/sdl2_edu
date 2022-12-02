#include "../headers/dot.hpp"
#include "../headers/game_class.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#include <vector>

bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB= b.y + b.h;

	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}

	return true;
}

Dot::Dot() {
	mPosX = 0;
	mPosY = 0;

	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

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

void Dot::move(SDL_Rect &wall) {
	mPosX += mVelX;
	mCollider.x = mPosX;

	if (mPosX + DOT_WIDTH > SCREEN_WIDTH ||
		  mPosX < 0 || 
		  checkCollision(mCollider, wall)) {
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}
	
	mPosY += mVelY;
	mCollider.y = mPosY;

	if (mPosY + DOT_HEIGHT > SCREEN_HEIGHT ||
		  mPosY < 0 ||
		  checkCollision(mCollider, wall)) {
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}

void Dot::resetSizeFromTexture() {
	DOT_WIDTH = gTexture->getWidth();
	DOT_HEIGHT = gTexture->getHeight();
	mCollider.h = DOT_HEIGHT;
	mCollider.w = DOT_WIDTH;
}

void Dot::setTexture(LTexture *newTexture) {
	gTexture = newTexture;
	resetSizeFromTexture();
}

void Dot::render() {
	gTexture->render(mPosX, mPosY);
}