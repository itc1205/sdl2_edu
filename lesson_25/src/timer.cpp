#include "../headers/timer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

LTimer::LTimer() {
	mStartTicks = 0;
	mPausedTicks = 0;
	mPaused = false;
	mStarted = false;
}

void LTimer::start() {
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
	mPaused = false;
	mStarted = true;
}

void LTimer::stop() {
	mStarted = false;
	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause() {
	if (mStarted && !mPaused) {
		mPausedTicks = SDL_GetTicks() - mStartTicks;

		mPaused = true;
		mStartTicks = 0;
	}
}

void LTimer::unpause() {
	if (mStarted && mPaused) {
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		mPaused = false;
		mPausedTicks = 0;
	}
}

Uint32 LTimer::getTicks() {

	if (mStarted) {
		if (mPaused) {
			return mPausedTicks;
		} else {
			return SDL_GetTicks() - mStartTicks;
		}
	}

	return 0;
}

bool LTimer::isStarted() {
	return mStarted;
}

bool LTimer::isPaused() {
	return mPaused && mStarted;
}