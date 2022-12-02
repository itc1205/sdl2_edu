#include "../headers/texture.hpp"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <cstdio>

LTexture::LTexture() {
  printf("Calling constructor for texture...\n");
  mTexture = nullptr;
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

  SDL_SetColorKey(loadedSurface, SDL_TRUE,
                  SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

  if (newTexture == nullptr) {
    printf("SDL_Texture error: %s\n", SDL_GetError());
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

void LTexture::render(int x, int y, SDL_Rect* clip, double angle,
                      SDL_Point* center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  if (clip != nullptr) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

int LTexture::getHeight() { return mHeight; }

int LTexture::getWidth() { return mWidth; }

void LTexture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

#ifdef TTF_MAJOR_VERSION
bool LTexture::loadFromRenderedText(std::string text, SDL_Color color, TTF_Font* font)
{
  free();
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

  if (textSurface == nullptr) {
    printf("Failed loading fonts: %s\n", TTF_GetError());
    SDL_FreeSurface(textSurface);
    return false;
  }

  mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

  if (mTexture == nullptr) {
    printf("Failed to create a texture from font: %s\n", SDL_GetError());
    SDL_FreeSurface(textSurface);
    return false;
  }

  mWidth = textSurface->w;
  mHeight = textSurface->h;

  SDL_FreeSurface(textSurface);

  return true;
}
#endif

void LTexture::setRenderer(SDL_Renderer *newRenderer) {
  gRenderer = newRenderer;
}