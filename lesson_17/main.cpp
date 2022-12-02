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

#include "headers/button.hpp"
#include "headers/game_class.hpp"
#include "headers/texture.hpp"

int main(int argc, char const *argv[]) {
  Game::init();

  Game game;

  // LButton buttons[4];

  game.gFont = TTF_OpenFont("assets/Minecraft.ttf", 28);

  SDL_Event e;

  bool isRunning = true;

  LButton buttons[4];

  LTexture textures[2];
  textures[0].setRenderer(game.gRenderer);
  textures[1].setRenderer(game.gRenderer);

  textures[0].loadFromFile("assets/button.png");

  for (int i = 0; i < 4; ++i) {
    buttons[i].setRenderer(game.gRenderer);
    buttons[i].setTexture(&textures[0]);
  }

  textures[1].loadFromRenderedText("Someone says: \"Hewwo World!!\"",
                                   SDL_Color{0, 0, 0}, game.gFont);

  SDL_Rect gSpriteClips[4];

  for (int i = 0; i < 4; ++i) {
    gSpriteClips[i].h = 200;
    gSpriteClips[i].w = 300;
    gSpriteClips[i].x = 0;
    gSpriteClips[i].y = 200 * i;
  }

  int cur_x = 0, cur_y = 0;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      buttons[i + j].setPos(cur_x, cur_y);
      cur_y += 200;
    }
    cur_y = 0;
    cur_x += 300;
  }
  buttons[3].setPos(0, 200);

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
      for (int i = 0; i < 4; ++i) {
        buttons[i].handleEvent(&e);
      }
    }

    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);

    for (int i = 0; i < 4; ++i) {
      buttons[i].render(gSpriteClips);
    }

    textures[1].render((SCREEN_WIDTH - textures[1].getWidth()) / 2,
                       (SCREEN_HEIGHT - textures[1].getHeight()) - 28);

    SDL_RenderPresent(game.gRenderer);
  }
  return 0;
}
