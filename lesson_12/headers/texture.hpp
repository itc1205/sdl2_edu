#include <SDL2/SDL_stdinc.h>
#ifndef _texture_h_
#define _texture_h_ value

#include <string>
#include <SDL2/SDL.h>

class LTexture {
public:
	LTexture(SDL_Renderer* newRenderer);
	~LTexture();
	
	bool loadFromFile(std::string);

	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void render(int x, int y, SDL_Rect* clip = nullptr);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	SDL_Renderer* gRenderer;
	int mWidth;
	int mHeight;
};

#endif