#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "headers/button.hpp"
#include "headers/game_class.hpp"
#include "headers/texture.hpp"\

bool load_media(LTexture textures[], Game *game) {
  textures[0].loadFromRenderedText("Sound of number 1 started playing i guuess",
                                    SDL_Color {0, 0, 0}, game->gFont);
  textures[1].loadFromRenderedText("Sound of number 2 started playing i guuess",
                                    SDL_Color {0, 0, 0}, game->gFont);
  textures[2].loadFromRenderedText("Sound of number 3 started playing i guuess",
                                    SDL_Color {0, 0, 0}, game->gFont);
  textures[3].loadFromRenderedText("Sound of number 4 started playing i guuess",
                                    SDL_Color {0, 0, 0}, game->gFont);
  textures[4].loadFromRenderedText("Music started playing i guuess",
                                    SDL_Color {0, 0, 0}, game->gFont);

  textures[5].loadFromRenderedText("Stopped music from playing i guuess",
                                    SDL_Color {0, 0, 0}, game->gFont);

  textures[6].loadFromRenderedText("\"The music is our rescue! Its like a healing potion...\"",
                                   SDL_Color{0, 0, 0}, game->gFont);
  return true;
}

int main(int argc, char const *argv[]) {
  Game::init();

  Game game;

  // LButton buttons[4];

  game.gFont = TTF_OpenFont("assets/Minecraft.ttf", 28);

  Mix_Chunk *chunks[4];
  Mix_Music *music = nullptr;

  music = Mix_LoadMUS("assets/beat.wav");

  chunks[0] = Mix_LoadWAV("assets/low.wav");
  chunks[1] = Mix_LoadWAV("assets/medium.wav");
  chunks[2] = Mix_LoadWAV("assets/high.wav");
  chunks[3] = Mix_LoadWAV("assets/scratch.wav");


  SDL_Event e;

  bool isRunning = true;

  LTexture textures[7];
  
  for (int i = 0; i < 7; ++i)
  {
    textures[i].setRenderer(game.gRenderer);
  }

  load_media(textures, &game);
  

  LTexture* cur_texture = &textures[6];

  while (isRunning) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }

    SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game.gRenderer);

    const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

    if (currentKeyState[SDL_SCANCODE_1]) {
      cur_texture = &textures[0];
      Mix_PlayChannel(-1, chunks[0], 1);
    }
    else if (currentKeyState[SDL_SCANCODE_2]) {
      cur_texture = &textures[1];
      Mix_PlayChannel(-1, chunks[1], 1);

    }
    else if (currentKeyState[SDL_SCANCODE_3]) {
      cur_texture = &textures[2];
      Mix_PlayChannel(-1, chunks[2], 1);

    }
    else if (currentKeyState[SDL_SCANCODE_4]) {
      cur_texture = &textures[3];
      Mix_PlayChannel(-1, chunks[3], 1);
      
    }
    else if (currentKeyState[SDL_SCANCODE_5]) {
      cur_texture = &textures[4];
      if (Mix_PlayingMusic() == false) {
        Mix_PlayMusic(music, 0);
      } else {
        if (Mix_PausedMusic()) {
          Mix_ResumeMusic();
        } else {
          Mix_PauseMusic();
        }
      }
    }
    else if (currentKeyState[SDL_SCANCODE_0]) {
      cur_texture = &textures[5];
      Mix_HaltMusic();
    }

    cur_texture->render((SCREEN_WIDTH - cur_texture->getWidth()) / 2,
                         cur_texture->getHeight() + 28);

    textures[6].render((SCREEN_WIDTH - textures[6].getWidth()) / 2,
                       (SCREEN_HEIGHT - textures[6].getHeight()) - 28);

    SDL_RenderPresent(game.gRenderer);
  }

  for (int i = 0; i < 4; ++i)
  {
    Mix_FreeChunk( chunks[i] );
    chunks[i] = nullptr;
  }
  Mix_FreeMusic(music);
  return 0;
}
