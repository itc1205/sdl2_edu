#include "headers/game_class.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#include <string>


SDL_Texture *loadTexture(std::string path, SDL_Renderer *gRenderer) {
  // The final texture
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}

int main(int argc, char const *argv[]) {
  Game game;

  SDL_Event e;

  bool isRunning = true;

  SDL_Texture* first_texture = loadTexture("assets/texture1.jpg", game.gRenderer);
  SDL_Texture* second_texture = loadTexture("assets/texture2.jpg", game.gRenderer);
  SDL_Texture* third_texture = loadTexture("assets/texture3.jpg", game.gRenderer);

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }

    SDL_Rect topLeftViewPort;
    topLeftViewPort.x = 0;
    topLeftViewPort.y = 0;
    topLeftViewPort.w = 640 / 2;
    topLeftViewPort.h = 480 / 2;
    SDL_RenderSetViewport(game.gRenderer, &topLeftViewPort);
    SDL_RenderCopy(game.gRenderer, first_texture, nullptr, nullptr);

    SDL_Rect topRightViewPort;
    topRightViewPort.x = 640 / 2;
    topRightViewPort.y = 0;
    topRightViewPort.w = 640 / 2;
    topRightViewPort.h = 480 / 2;
    SDL_RenderSetViewport(game.gRenderer, &topRightViewPort);
    SDL_RenderCopy(game.gRenderer, second_texture, nullptr, nullptr);


    SDL_Rect bottomViewPort;
    bottomViewPort.x = 0;
    bottomViewPort.y = 480 / 2;
    bottomViewPort.w = 640;
    bottomViewPort.h = 480 / 2;
    SDL_RenderSetViewport(game.gRenderer, &bottomViewPort);
    SDL_RenderCopy(game.gRenderer, third_texture, nullptr, nullptr);

    SDL_RenderPresent(game.gRenderer);
  }

  return 0;
}