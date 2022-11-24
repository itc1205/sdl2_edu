#include <cinttypes>
#include <stdio.h>

#include <SDL2/SDL.h>

bool init();

bool load_media();

bool close();

SDL_Window *gWindow = nullptr;

SDL_Surface *gScreenSurface = nullptr;

SDL_Surface *helloWorld = nullptr;

int main(int argc, char const *argv[])
{
	if (!init() || !load_media()) {
		printf("%s\n", SDL_GetError());
		return 1;
	}



	
	return 0;
}

