#include <SDL2/SDL_stdinc.h>
#ifndef _timer_h_
#define _timer_h_ value

class LTimer{
public:
	LTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	Uint32 mStartTicks;

	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;
};

#endif