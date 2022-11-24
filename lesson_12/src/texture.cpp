#include "../headers/texture.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <cstddef>

LTexture::LTexture(SDL_Renderer *newRenderer) {
	mTexture = nullptr;
	gRenderer = newRenderer;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	printf("Calling destructor for texutre...\n");
	free();
}

bool LTexture::loadFromFile(std::string path) {
	free();
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr) {
		printf("SDL_Image error: %s", SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	if (newTexture == nullptr) {
		printf("SDL_Texture error: %s", SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}
	
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);

	mTexture = newTexture;
	return mTexture != nullptr;
}

void LTexture::free() {
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

int LTexture::getHeight() {
	return mHeight;
}

int LTexture::getWidth() {
	return mWidth;
}