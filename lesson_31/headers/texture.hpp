#ifndef _texture_h_
#define _texture_h_ value

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class LTexture {
 public:
  LTexture();
  ~LTexture();

  bool loadFromFile(std::string);

  #ifdef SDL_TTF_MAJOR_VERSION
  bool loadFromRenderedText(std::string text, SDL_Color color, TTF_Font* font);
  #endif
  void free();

  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  void setAlpha(Uint8 alpha);

  void setBlendMode(SDL_BlendMode blending);

  void setRenderer(SDL_Renderer *newRenderer);

  void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0,
              SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  int getWidth();
  int getHeight();

 protected:
  SDL_Texture* mTexture;
  SDL_Renderer* gRenderer;
  int mWidth;
  int mHeight;
};

#endif