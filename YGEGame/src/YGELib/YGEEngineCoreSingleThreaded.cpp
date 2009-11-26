#include "YGEEngineCoreSingleThreaded.h"
#include "YGESDLDisplay.h"
#include <SDL_thread.h> 
#include <SDL_ttf.h>



namespace YGECore {

	void YGEEngineCoreSingleThreaded::run(){

		debugout("starting the core");

		while(display->windowClosed == false && shutdownNow == false){

			//debugout("update the core");

			timer->startTimer();

			display->reset();
			display->update();



			processEvents();


			if(gamestate != NULL) {
				gamestate->update();

				updateSpaceList(gamestate->getSpacesToUpdate());

				renderSceneList(gamestate->getScenesToRender());

			}

			if(consoleEnabled) {
				console->draw();
			}

			calculateFPSRate();

			limitFPS();


		}

		debugout("stopping the core");
	}

	void YGEEngineCoreSingleThreaded::processEvents(){

		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			switch(event.type){
			case SDL_QUIT:
				display->notifyEvent(&event);
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
			case SDLK_BACKQUOTE:
				toggleConsole();
				break;
			default:
				if(consoleEnabled){
					console->insertKey(event.key.keysym);
				} else {
					input->notifyEvent(&event);
				}
				break;
				}
				break;
			case SDL_KEYUP:
				input->notifyEvent(&event);
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:


				break;
			}

		}

	}

	void YGEEngineCoreSingleThreaded::renderSceneList(YGETimeSpace::YGESceneList *list){
		for(YGETimeSpace::YGESceneList::iterator iter = list->begin(); iter != list->end(); iter++){



			(*iter).second->setCameraMatrixRotation((*iter).first->getRootEntity());
			(*iter).first->getSkybox()->draw();
			(*iter).second->setCameraMatrix((*iter).first->getRootEntity());
			(*iter).first->getSunlight()->draw();

			
			// @todo this doesnt belong here
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			(*iter).first->getRootEntity()->render();
		}
	}
	void YGEEngineCoreSingleThreaded::updateSpaceList(YGETimeSpace::YGESpaceList *list){
		for(YGETimeSpace::YGESpaceList::iterator iter = list->begin(); iter != list->end(); iter++){

			(*iter)->timeStep(delta);
			(*iter)->getRootEntity()->update(delta);
		}
	}


	void YGEEngineCoreSingleThreaded::calculateFPSRate(){

		delta = timer->stopTimer();

		//debugout("updating the core took ms");
		//debugout(delta / 1000);

	}

	void YGEEngineCoreSingleThreaded::limitFPS(){
		if(delta < 10000) {
			//debugout("less then 10 ms, wait a little");

			SDL_Delay(Uint32((10000-delta) / 1000));
		}
	}


	void YGEEngineCoreSingleThreaded::update(){


	}

	void YGEEngineCoreSingleThreaded::init(){

		delta = 1000;


		debugout("initialize the core");
		debugout("using SDL");


		YGELogger::getInstance()->log("Initializing SDL Video");
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			YGELogger::getInstance()->log("Unable to initialize SDL");
			//fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
			return;
		}

		TTF_Init();

		console = new YGEConsole();
		YGELogger::getInstance()->setConsole(console);
		display = new YGESDLDisplay();
		input = new YGESDLInputManager();

		timer = new YGETimer();
		timeSinceGameStarted = new YGETimer();
		timeSinceGameStarted->startTimer();



		logger = YGELogger::getInstance();
		display->init();
		console->init(this);

	}







	void YGEEngineCoreSingleThreaded::shutdown(){
		debugout("prepare to shut down!");
		shutdownNow = true;
	}

}