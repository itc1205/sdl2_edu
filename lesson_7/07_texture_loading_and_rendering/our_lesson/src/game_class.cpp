#include "../headers/game_class.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>


bool Game::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
      return false;
    }
    return true;
}

SDL_Texture *Game::loadTexture(std::string path) {
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
        printf("Unable to create texture from %s! SDL Error: %s\n",
               path.c_str(), SDL_GetError());
      }

      // Get rid of old loaded surface
      SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool Game::loadMedia() {
	bool success = true;
    printf("Loading media...\n");
    // Load PNG texture
    gTexture = loadTexture("texture.png");
    if (gTexture == NULL) {
      printf("Failed to load texture image!\n");
      success = false;
    }
    return success;
}

Game::Game() {
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    printf("Calling constructor...\n");
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    } else {
      // Create renderer for window
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
      } else {
        // Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
        }
        loadMedia();
      }
    }
}

Game::~Game() {
	printf("calling destructor...\n");
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window	
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}