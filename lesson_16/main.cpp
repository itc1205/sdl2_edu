#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "headers/game_class.hpp"
#include "headers/texture.hpp"

int main(int argc, char const *argv[]) {

  Game::init();
  
  Game game;



  game.gFont = TTF_OpenFont("assets/Minecraft.ttf", 28);

  SDL_Event e;

  bool isRunning = true;

  std::vector<LTexture> textures;

  textures.push_back(LTexture(game.gRenderer));

  textures[0].loadFromRenderedText("Pykhiy was here uwu!", SDL_Color {0, 0, 0}, game.gFont);

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
        continue;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        }
      }
      SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(game.gRenderer);

      textures[0].render( ( SCREEN_WIDTH - textures[0].getWidth() ) / 2, ( SCREEN_HEIGHT - textures[0].getHeight() ) / 2 );


      SDL_RenderPresent(game.gRenderer);
    }
  }
  return 0;
}
