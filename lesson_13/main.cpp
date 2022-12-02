#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

#include <string>

#include <vector>

#include "headers/game_class.hpp"
#include "headers/texture.hpp"

int main(int argc, char const *argv[]) {
  Game game;

  SDL_Event e;

  bool isRunning = true;

  std::vector<LTexture> textures;

  textures.push_back(LTexture(game.gRenderer));
  textures.push_back(LTexture(game.gRenderer));

  textures[0].loadFromFile("assets/background.jpg");
  
  textures[1].loadFromFile("assets/alpha100.png");
  textures[1].setBlendMode(SDL_BLENDMODE_BLEND);
  
  Uint8 alpha = 0;

  Uint8 step = 32;

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
        continue;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_w:

            if (alpha + step > 255) {
              alpha = 255;
            } else {
              alpha += step;
            }

            break;

          case SDLK_s:
            if (alpha - step < 0) {
              alpha = 0;
            } else {
              alpha -= step;
            }

            break;
        }
      }

      SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(game.gRenderer);

      textures[0].render(0, 0);
      
      textures[1].setAlpha(alpha);
      textures[1].render(0, 0);

      SDL_RenderPresent(game.gRenderer);
    }
  }
  return 0;
}
