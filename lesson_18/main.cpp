#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


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

  LTexture textures[6];
  
  for (int i = 0; i < 6; ++i)
  {
    textures[i].setRenderer(game.gRenderer);
  }

  textures[0].loadFromFile("assets/up.png");
  textures[1].loadFromFile("assets/down.png");
  textures[2].loadFromFile("assets/right.png");
  textures[3].loadFromFile("assets/left.png");
  textures[4].loadFromFile("assets/press.png");

  textures[5].loadFromRenderedText("Someone says: \"Hewwo World!!\"",
                                   SDL_Color{0, 0, 0}, game.gFont);

  LTexture* cur_texture = nullptr;

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }

    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);

    const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

    if (currentKeyState[SDL_SCANCODE_UP]) {
      cur_texture = &textures[0];
    }
    else if (currentKeyState[SDL_SCANCODE_DOWN]) {
      cur_texture = &textures[1];
    }
    else if (currentKeyState[SDL_SCANCODE_RIGHT]) {
      cur_texture = &textures[2];
    }
    else if (currentKeyState[SDL_SCANCODE_LEFT]) {
      cur_texture = &textures[3];
    }
    else {
      cur_texture = &textures[4];
    } 

    cur_texture->render(0, 0);

    textures[5].render((SCREEN_WIDTH - textures[5].getWidth()) / 2,
                       (SCREEN_HEIGHT - textures[5].getHeight()) - 28);

    SDL_RenderPresent(game.gRenderer);
  }
  return 0;
}
