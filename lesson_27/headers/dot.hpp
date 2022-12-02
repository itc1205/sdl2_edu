#ifndef _dot_h_
#define _dot_h_ value
#include <SDL2/SDL.h>
#include "../headers/texture.hpp"

class Dot {
public:
  

  Dot();

  void handleEvent(SDL_Event &e);

  void move(SDL_Rect& wall);

  void render();

  void setTexture (LTexture *newTexture);

  void resetSizeFromTexture();

private:
  LTexture *gTexture;
  int mPosX, mPosY;
  int mVelX, mVelY;

  int DOT_WIDTH = 18;
  int DOT_HEIGHT = 18;
  int DOT_VEL = 5; 

  SDL_Rect mCollider;
};
#endif