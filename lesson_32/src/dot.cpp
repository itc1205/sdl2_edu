#include "../headers/dot.hpp"
#include "../headers/game_class.hpp"

#include <SDL2/SDL.h>
#include <cstdio>
#include <vector>



Dot::Dot(int x, int y) {
	printf("Initting a dot\n");
	mPosX = x;
	mPosY = y;

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
	//Move the dot left or right
    mPosX += mVelX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX  < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}


void Dot::setTexture(LTexture *newTexture) {
	gTexture = newTexture;
}

void Dot::render(int camPosX, int camPosY) {
	gTexture->render(mPosX - camPosX, mPosY - camPosY);
}

int Dot::getPosX() {
    return mPosX;
}

int Dot::getPosY() {
    return mPosY;
}