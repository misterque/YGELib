#include "YGESDLTimer.h"
#include <SDL.h>

YGESDLTimer::YGESDLTimer(){
	basetime = SDL_GetTicks() * 1000;
}

long long YGESDLTimer::getTime(){
	return SDL_GetTicks() * 1000 - basetime;
}

void YGESDLTimer::startTimer(){
	basetime = SDL_GetTicks() * 1000;

}

long long YGESDLTimer::stopTimer(){
	return stoppedTime = getTime();
}