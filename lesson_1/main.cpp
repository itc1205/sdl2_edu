#include <SDL2/SDL.h>
#include <stdio.h>

const int HEIGHT = 640;
const int WIDTH = 480;

int main(int argc, char const* argv[]) {
  SDL_Window* gWindow = nullptr;

  SDL_Surface* gSurface = nullptr;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error occured; SDL_Error: %s", SDL_GetError());
    return 1;
  }

  gWindow = SDL_CreateWindow("Hello, world", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                             SDL_WINDOW_SHOWN);
  if (gWindow == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 0;
  }
  gSurface = SDL_GetWindowSurface( gWindow );

              //Fill the surface white
              SDL_FillRect( gSurface, NULL, SDL_MapRGB( gSurface->format, 0xFF, 0xFF, 0xFF ) );
              
              //Update the surface
              SDL_UpdateWindowSurface( gWindow );

              //Hack to get window to stay up
              SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

  return 0;
}