#include "headers/game_class.hpp"
#include "headers/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#include <string>


int main(int argc, char const *argv[]) {
  Game game;

  SDL_Event e;

  bool isRunning = true;

  SDL_Rect gSpriteClips[4];
  LTexture gSpriteSheetTexture(game.gRenderer);
  gSpriteSheetTexture.loadFromFile( "assets/sprites.png" );
  //Set top left sprite
  gSpriteClips[ 0 ].x =   0;
  gSpriteClips[ 0 ].y =   0;
  gSpriteClips[ 0 ].w = 100;
  gSpriteClips[ 0 ].h = 100;

  //Set top right sprite
  gSpriteClips[ 1 ].x = 100;
  gSpriteClips[ 1 ].y =   0;
  gSpriteClips[ 1 ].w = 100;
  gSpriteClips[ 1 ].h = 100;
  
  //Set bottom left sprite
  gSpriteClips[ 2 ].x =   0;
  gSpriteClips[ 2 ].y = 100;
  gSpriteClips[ 2 ].w = 100;
  gSpriteClips[ 2 ].h = 100;

  //Set bottom right sprite
  gSpriteClips[ 3 ].x = 100;
  gSpriteClips[ 3 ].y = 100;
  gSpriteClips[ 3 ].w = 100;
  gSpriteClips[ 3 ].h = 100;

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }
    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);

     //Render top left sprite
    gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ] );

    //Render top right sprite
    gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

    //Render bottom left sprite
    gSpriteSheetTexture.render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

    //Render bottom right sprite
    gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );
    
    
    SDL_RenderPresent(game.gRenderer);
  }

  return 0;
}