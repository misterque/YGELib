#include "YGEEngineCore.h"
#include "YGESDLDisplay.h"

namespace YGECore {

void YGEEngineCore::run(){

#ifdef _DEBUG
	logger->log("starting the core");
#endif

	while(display->windowClosed == false){
		update();

	}

#ifdef _DEBUG
	logger->log("stopping the core");
#endif
}

void YGEEngineCore::update(){

#ifdef _DEBUG
	logger->log("update the core");
#endif

	timer->startTimer();
	//@todo rename method to update?
	display->reset();
	display->update();
	input->update();
	long long delta = timer->stopTimer();

#ifdef _DEBUG
	logger->log("updating the core took ms");
	logger->log(delta / 1000);
#endif

	if(delta < 10000) {
#ifdef _DEBUG
		logger->log("less then 10 ms, wait a little");
#endif

		SDL_Delay((10000-delta) / 1000);
	}

}

void YGEEngineCore::init(){

#ifdef _DEBUG
	logger->log("initialize the core");
#ifdef USE_SDL
	logger->log("using SDL");
#endif
#endif

#ifdef USE_SDL

	YGELogger::getInstance()->log("Initializing SDL Video");
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		YGELogger::getInstance()->log("Unable to initialize SDL");
		//fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return;
	}

	display = new YGESDLDisplay();
	input = new YGESDLInputManager();

	timer = new YGESDLTimer();

#endif

	logger = YGELogger::getInstance();
	display->init();

}

void YGEEngineCore::shutdown(){
	
#ifdef USE_SDL
	SDL_Quit();
#endif

}

YGEEngineCore::YGEEngineCore(){

}

YGEEngineCore::~YGEEngineCore(){

}

}