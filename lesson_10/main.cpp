#include "headers/game_class.hpp"
#include "headers/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#include <string>


int main(int argc, char const *argv[]) {
  Game game;

  SDL_Event e;

  bool isRunning = true;

  LTexture gFooTexture(game.gRenderer);
  LTexture gBackgroundTexture(game.gRenderer);

  gFooTexture.loadFromFile("assets/foo.png");
  gBackgroundTexture.loadFromFile("assets/background.png");

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }
    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);

    gBackgroundTexture.render(0, 0);

    gFooTexture.render(240, 190);
    
    SDL_RenderPresent(game.gRenderer);
  }

  return 0;
}