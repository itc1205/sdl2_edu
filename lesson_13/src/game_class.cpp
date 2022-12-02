#include "../headers/game_class.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <cstdio>

bool Game::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Init Error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

void Game::create_window() {
  printf("Creating window...\n");
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 
  {
  	printf("Warning: Liniear texture filtering is not enabled!\n");
  }

  gWindow = SDL_CreateWindow("CHINGIZ?????", 0, 0, 640, 480, 0);
  if (gWindow == nullptr) {
  	printf("Window error: %s\n", SDL_GetError());
  }

}

void Game::create_renderer() {
	printf("Creating renderer...\n");
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr) {
		printf("Renderer error: %s\n", SDL_GetError());
	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

Game::Game() {
  create_window();
  create_renderer();
}

Game::~Game() {
  printf("Calling destructor...\n");
  //Destroy window  
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}