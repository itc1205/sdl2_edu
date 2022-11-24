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

	void render(int x, int y);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	SDL_Renderer* gRenderer;
	int mWidth;
	int mHeight;
};

#endif