#include "headers/game_class.hpp"

int main(int argc, char const *argv[]) {
  if (!Game::init()) {
    return 1;
  }

  Game game;

  bool quit = false;

  // Event handler
  SDL_Event e;

  // While application is running
  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // Clear screen
    SDL_RenderClear(game.gRenderer);

    // Render texture to screen
    SDL_RenderCopy(game.gRenderer, game.gTexture, NULL, NULL);

    // Update screen
    SDL_RenderPresent(game.gRenderer);
  }

  return 0;
}
