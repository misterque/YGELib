#include "YGETimer.h"
#include <SDL.h>

namespace YGECore {


YGETimer::YGETimer(){
	basetime = SDL_GetTicks() * 1000;
}

long long YGETimer::getTime(){
	return SDL_GetTicks() * 1000 - basetime;
}

void YGETimer::startTimer(){
	basetime = SDL_GetTicks() * 1000;

}

long long YGETimer::stopTimer(){
	return stoppedTime = getTime();
}

}