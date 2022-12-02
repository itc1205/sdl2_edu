#include "headers/button.hpp"
#include "headers/game_class.hpp"
#include "headers/texture.hpp"
#include "headers/timer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>

#include <string>
#include <vector>


bool load_media(LTexture textures[], Game *game) {
  
  textures[0].loadFromRenderedText("Press spacebar to reset a timer or return to pause it", SDL_Color {0, 0, 0}, game->gFont);
  textures[2].loadFromRenderedText("Itc says: Little naps are awesome for your mental health!", SDL_Color {0, 0, 0}, game->gFont);

  return true;
}

int main(int argc, char const *argv[]) {
  Game::init();

  Game game;

  LTimer timer;


  // LButton buttons[4];

  game.gFont = TTF_OpenFont("assets/Minecraft.ttf", 18);


  SDL_Event e;

  bool isRunning = true;

  LTexture textures[3];
  
  for (int i = 0; i < 3; ++i)
  {
    textures[i].setRenderer(game.gRenderer);
  }

  load_media(textures, &game);
  
  std::stringstream timeText;  

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
      else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
        if (timer.isStarted()) {
          timer.stop();
        } else {
          timer.start();
        }
      } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
        if (timer.isPaused()) {
          timer.unpause();
        } else {
          timer.pause();
        }
      }
    }

    timeText.str("");
    timeText << "Seconds passed since start time " << timer.getTicks() / 1000.0f;

    textures[1].loadFromRenderedText(timeText.str().c_str(), SDL_Color {0, 0, 0}, game.gFont);

    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);



    textures[0].render((SCREEN_WIDTH - textures[0].getWidth()) / 2,
                         textures[0].getHeight() + 28);

    textures[1].render((SCREEN_WIDTH - textures[1].getWidth()) / 2,
                          (SCREEN_HEIGHT - textures[1].getHeight()) / 2);

    textures[2].render((SCREEN_WIDTH - textures[2].getWidth()) / 2,
                       (SCREEN_HEIGHT - textures[2].getHeight()) - 28);

    SDL_RenderPresent(game.gRenderer);
  }
  return 0;
}
