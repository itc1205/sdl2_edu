#ifndef _dot_h_
#define _dot_h_ value
#include <SDL2/SDL.h>
#include <vector>
#include "../headers/texture.hpp"


class Dot {
public:
  
  int DOT_WIDTH = 20;
  int DOT_HEIGHT = 20;
  int DOT_VEL = 10; 

  Dot(int x, int y);

  void handleEvent(SDL_Event &e);

  void move();

  void render(int camX = 0, int camY = 0);

  void setTexture (LTexture *newTexture);

  int getPosX();
  int getPosY();

private:
  LTexture *gTexture;
  int mPosX, mPosY;
  int mVelX, mVelY;

  
};
#endif