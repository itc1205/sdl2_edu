#ifndef _dot_h_
#define _dot_h_ value
#include <SDL2/SDL.h>
#include "../headers/texture.hpp"

class Dot {
public:
  static const int DOT_WIDTH = 18;
  static const int DOT_HEIGHT = 18;

  static const int DOT_VEL = 10;

  Dot();

  void handleEvent(SDL_Event &e);

  void move();

  void render();

  void setTexture (LTexture *newTexture);

private:
  LTexture *gTexture;
  int mPosX, mPosY;
  int mVelX, mVelY;
};
#endif