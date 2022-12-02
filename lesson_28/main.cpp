#include "headers/button.hpp"
#include "headers/game_class.hpp"
#include "headers/texture.hpp"
#include "headers/timer.hpp"
#include "headers/dot.hpp"


#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>

#include <string>
#include <vector>


bool load_media(LTexture textures[], Game *game) {
  
  textures[0].loadFromFile("assets/normal.jpg");
  textures[2].loadFromRenderedText("Dots are so entertaining uwu!", SDL_Color {0, 0, 0}, game->gFont);

  return true;
}

int main(int argc, char const *argv[]) {
  Game::init();

  Game game;

  LTimer fpstimer;

  LTimer captimer;

  Dot dot(0, 0);

  Dot otherDot(320, 200);

  // LButton buttons[4];

  game.gFont = TTF_OpenFont("assets/Minecraft.ttf", 18);

  SDL_Event e;

  bool isRunning = true;

  //Loading textures in memory
  LTexture textures[3];
  
  for (int i = 0; i < 3; ++i)
  {
    textures[i].setRenderer(game.gRenderer);
  }

  load_media(textures, &game);
  

  dot.setTexture(&textures[0]);
  otherDot.setTexture(&textures[0]);

  std::stringstream timeText;  

  int counted_frames = 0;
  fpstimer.start();

  while (isRunning) {
    captimer.start();
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
      dot.handleEvent(e);
    }

    float avgFPS = counted_frames / (fpstimer.getTicks() / 1000.0f);
    if (avgFPS > 2000000) {
      avgFPS = 0;
    }
    timeText.str("");
    timeText << "Average fps " << avgFPS;

    textures[1].loadFromRenderedText(timeText.str().c_str(), SDL_Color {0, 0, 0}, game.gFont);

    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);



    textures[1].render((SCREEN_WIDTH - textures[1].getWidth()) / 2,
                         textures[1].getHeight() + 28);

    dot.move(otherDot.getColliders());
    otherDot.render();
    dot.render();

    textures[2].render((SCREEN_WIDTH - textures[2].getWidth()) / 2,
                       (SCREEN_HEIGHT - textures[2].getHeight()) - 28);

    SDL_RenderPresent(game.gRenderer);
    counted_frames++;

    int frameTicks = captimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
      SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
  }
  return 0;
}
