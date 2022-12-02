#include <SDL2/SDL_rect.h>
#ifndef _dot_h_
#define _dot_h_ value
#include <SDL2/SDL.h>
#include <vector>
#include "../headers/texture.hpp"

class Dot {
public:
  

  Dot(int x, int y);

  void handleEvent(SDL_Event &e);

  void move(std::vector<SDL_Rect> &other_colliders);

  void render();

  void setTexture (LTexture *newTexture);

  std::vector<SDL_Rect>& getColliders();

private:
  LTexture *gTexture;
  int mPosX, mPosY;
  int mVelX, mVelY;

  std::vector<SDL_Rect> mColliders;

  void shiftColliders();

  int DOT_WIDTH = 20;
  int DOT_HEIGHT = 20;
  int DOT_VEL = 1; 
};
#endif