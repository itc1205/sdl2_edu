#include "headers/game_class.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>


int main(int argc, char const *argv[]) {
  Game game;

  SDL_Event e;

  bool isRunning = true;

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }
    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);

    SDL_Rect fillRect = {640 / 4, 480 / 4, 640 / 2, 480 / 2};
    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(game.gRenderer, &fillRect);

    SDL_Rect outlineRect = {640 / 6, 480 / 6, 640 * 2 / 3, 480 * 2 / 3};
    SDL_SetRenderDrawColor(game.gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(game.gRenderer, &outlineRect);

    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawLineF(game.gRenderer, 640 / 2, 0, 640 / 2, 480);

    SDL_SetRenderDrawColor(game.gRenderer, 0x00, 0x00, 0xFF, 0xFF);

    for (int i = 0; i < 640; i += 4) {
      SDL_RenderDrawPoint(game.gRenderer, i, 480 / 2);
    }

    SDL_RenderPresent(game.gRenderer);
  }

  return 0;
}