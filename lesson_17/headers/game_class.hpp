#ifndef _game_class_hpp
#define _game_class_hpp

#include <SDL2/SDL_ttf.h>
#define TITLE "CHINGIZ???"


#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdio>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;



class Game {
public:
  SDL_Renderer *gRenderer = nullptr;
  SDL_Window *gWindow = nullptr;
  TTF_Font *gFont = nullptr;

  static bool init();

  void create_window();
  void create_renderer();

  Game();
  ~Game();
};

#endif
