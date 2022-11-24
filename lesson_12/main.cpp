#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

#include <string>

#include "headers/game_class.hpp"
#include "headers/texture.hpp"

int main(int argc, char const *argv[]) {
  Game game;

  SDL_Event e;

  bool isRunning = true;

  LTexture gModTexture(game.gRenderer);
  gModTexture.loadFromFile("assets/full.png");

  Uint8 r = 255;
  Uint8 g = 255;
  Uint8 b = 255;

  Uint8 step = 32;
  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
        continue;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_q:
            r += step;
            break;
          case SDLK_w:
            g += step;
            break;
          case SDLK_e:
            b += step;
            break;
          case SDLK_a:
            r -= step;
            break;
          case SDLK_s:
            g -= step;
            break;
          case SDLK_d:
            b -= step;
            break;
        }
      }
      SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(game.gRenderer);

      gModTexture.setColor(r, g, b);
      gModTexture.render(0, 0);

      SDL_RenderPresent(game.gRenderer);
    }

  }
  return 0;
}