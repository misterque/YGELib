#include "YGECore.h"
#include "YGESDLDisplay.h"

void YGECore::run(){

	display->reset();
}

void YGECore::init(){

#ifdef USE_SDL

	YGELogger::getInstance()->log("Initializing SDL Video");
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		YGELogger::getInstance()->log("Unable to initialize SDL");
		//fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return;
	}
	atexit(SDL_Quit); // Clean it up nicely :)


	display = new YGESDLDisplay();

#endif

	display->init();

}