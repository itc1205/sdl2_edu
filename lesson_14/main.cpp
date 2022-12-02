#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
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

  const int WALKING_FRAMES = 4;
  SDL_Rect gSpriteClips[4];

  textures.push_back(LTexture(game.gRenderer));

  textures[0].loadFromFile("assets/foo.png");

  gSpriteClips[0].x = 0;
  gSpriteClips[0].y = 0;
  gSpriteClips[0].w = 64;
  gSpriteClips[0].h = 205;

  gSpriteClips[1].x = 64;
  gSpriteClips[1].y = 0;
  gSpriteClips[1].w = 64;
  gSpriteClips[1].h = 205;

  gSpriteClips[2].x = 128;
  gSpriteClips[2].y = 0;
  gSpriteClips[2].w = 64;
  gSpriteClips[2].h = 205;

  gSpriteClips[3].x = 192;
  gSpriteClips[3].y = 0;
  gSpriteClips[3].w = 64;
  gSpriteClips[3].h = 205;

  int current_frame = 0;


  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
        continue;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {}
      }

      SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(game.gRenderer);

      SDL_Rect* currentClip = &gSpriteClips[ current_frame / 4 ];
      textures[0].render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

      current_frame++;

      if (current_frame / 4 >= WALKING_FRAMES) {
        current_frame = 0;
      }


      SDL_RenderPresent(game.gRenderer);
    }
  }
  return 0;
}
