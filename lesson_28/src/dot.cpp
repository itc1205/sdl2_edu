#include "../headers/dot.hpp"
#include "../headers/game_class.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <cstdio>
#include <vector>

bool checkCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b) {
	 //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Go through the A boxes
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;
        for (int Bbox = 0; Bbox < b.size(); Bbox++) {
        	leftB = b[Bbox].x;
        	rightB = b[Bbox].x + a[Bbox].w;
        	topB = b[Bbox].y;
        	bottomB = b[Bbox].y + b[Bbox].h;
        	if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //A collision is detected
                return true;
            }
        }
    }
    return false;
}

void Dot::shiftColliders()
{
    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
    for( int set = 0; set < mColliders.size(); ++set )
    {
        //Center the collision box
        mColliders[ set ].x = mPosX + ( DOT_WIDTH - mColliders[ set ].w ) / 2;

        //Set the collision box at its row offset
        mColliders[ set ].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[ set ].h;
    }
}

std::vector<SDL_Rect>& Dot::getColliders()
{
    return mColliders;
}

Dot::Dot(int x, int y) {
	printf("Initting a dot\n");
	mPosX = x;
	mPosY = y;

	mVelX = 0;
	mVelY = 0;

	mColliders.resize( 11 );

	mColliders[ 0 ].w = 6;
    mColliders[ 0 ].h = 1;

    mColliders[ 1 ].w = 10;
    mColliders[ 1 ].h = 1;

    mColliders[ 2 ].w = 14;
    mColliders[ 2 ].h = 1;

    mColliders[ 3 ].w = 16;
    mColliders[ 3 ].h = 2;

    mColliders[ 4 ].w = 18;
    mColliders[ 4 ].h = 2;

    mColliders[ 5 ].w = 20;
    mColliders[ 5 ].h = 6;

    mColliders[ 6 ].w = 18;
    mColliders[ 6 ].h = 2;

    mColliders[ 7 ].w = 16;
    mColliders[ 7 ].h = 2;

    mColliders[ 8 ].w = 14;
    mColliders[ 8 ].h = 1;

    mColliders[ 9 ].w = 10;
    mColliders[ 9 ].h = 1;

    mColliders[ 10 ].w = 6;
    mColliders[ 10 ].h = 1;

	shiftColliders();
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

void Dot::move(std::vector<SDL_Rect> &walls) {
	mPosX += mVelX;

	shiftColliders();

	if (mPosX + DOT_WIDTH > SCREEN_WIDTH ||
		  mPosX < 0 || 
		  checkCollision(mColliders, walls)) {
		mPosX -= mVelX;
		shiftColliders();
	}
	
	mPosY += mVelY;

	if (mPosY + DOT_HEIGHT > SCREEN_HEIGHT ||
		  mPosY < 0 ||
		  checkCollision(mColliders, walls)) {
		mPosY -= mVelY;
		shiftColliders();
	}
}


void Dot::setTexture(LTexture *newTexture) {
	gTexture = newTexture;
}

void Dot::render() {
	gTexture->render(mPosX, mPosY);
}