#ifndef _game_class_h
#define _game_class_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Game {
public:
  SDL_Texture *gTexture = NULL;
  SDL_Window *gWindow = NULL;
  SDL_Renderer *gRenderer = NULL;

  static bool init();

  SDL_Texture *loadTexture(std::string path);

  bool loadMedia();
  
  Game();
  ~Game();
};

#endif