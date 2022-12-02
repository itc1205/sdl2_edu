#include <SDL2/SDL_rect.h>
#ifndef _dot_h_
#define _dot_h_ value
#include <SDL2/SDL.h>
#include <vector>
#include "../headers/texture.hpp"

struct Circle {
  int x, y;
  int r;
};

class Dot {
public:
  

  Dot(int x, int y);

  void handleEvent(SDL_Event &e);

  void move(SDL_Rect& square, Circle& circle);

  void render();

  void setTexture (LTexture *newTexture);

  Circle& getColliders();

private:
  LTexture *gTexture;
  int mPosX, mPosY;
  int mVelX, mVelY;

  Circle mCollider;

  void shiftColliders();

  int DOT_WIDTH = 20;
  int DOT_HEIGHT = 20;
  int DOT_VEL = 1; 
};
#endif