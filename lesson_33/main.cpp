#include <SDL2/SDL.h>
#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <sstream>
#include <string>
#include <vector>

#include "headers/button.hpp"
#include "headers/dot.hpp"
#include "headers/game_class.hpp"
#include "headers/texture.hpp"
#include "headers/timer.hpp"

bool load_media(LTexture textures[], Game *game) {
  game->gFont = TTF_OpenFont("assets/Minecraft.ttf", 18);

  return true;
}

int main(int argc, char const *argv[]) {
  Game::init();

  Game game;

  LTimer captimer;

  // Loading textures in memory
  LTexture textures[2];

  for (int i = 0; i < 2; ++i) {
    textures[i].setRenderer(game.gRenderer);
  }

  load_media(textures, &game);

  std::string inputText = "Some text";
  textures[0].loadFromRenderedText(inputText, SDL_Color{0, 0, 0}, game.gFont);

  SDL_Event e;

  bool isRunning = true;

  SDL_StartTextInput();

  while (isRunning) {
    captimer.start();

    bool renderText = false;

    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }

      else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() != 0) {
          inputText.pop_back();
          renderText = true;
        } else if (e.key.keysym.sym == SDLK_c &&
                   SDL_GetModState() & KMOD_CTRL) {
          SDL_SetClipboardText(inputText.c_str());
        } else if (e.key.keysym.sym == SDLK_v &&
                   SDL_GetModState() & KMOD_CTRL) {
          inputText = SDL_GetClipboardText();
          renderText = true;
        }
      }

      else if (e.type == SDL_TEXTINPUT) {
        if (!(SDL_GetModState() & KMOD_CTRL &&
              (e.text.text[0] == 'c' || e.text.text[0] == 'C' ||
               e.text.text[0] == 'v' || e.text.text[0] == 'V'))) {
          inputText += e.text.text;
          renderText = true;
        }
      }
    }

    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);

    if (renderText) {
      if (!inputText.empty()) {
        textures[0].loadFromRenderedText(inputText, SDL_Color{0, 0, 0},
                                         game.gFont);
      } else {
        textures[0].loadFromRenderedText("", SDL_Color{0, 0, 0}, game.gFont);
      }
    }
    textures[0].render((SCREEN_WIDTH - textures[0].getWidth()) / 2,
                       textures[0].getHeight() + 28);

    SDL_RenderPresent(game.gRenderer);

    int frameTicks = captimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
      SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
  }
  SDL_StopTextInput();
  return 0;
}
