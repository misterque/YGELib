#include "YGEEngineCoreSingleThreaded.h"
#include "YGESDLDisplay.h"
#include <SDL_thread.h> 
#include <SDL_ttf.h>

#include "YGEText.h"



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
				gamestate->update(delta);

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
		int t;
		timerGraphics->startTimer();

		for(YGETimeSpace::YGESceneList::iterator iter = list->begin(); iter != list->end(); iter++){



			if((*iter).first->hasSkybox()){
				(*iter).second->setCameraMatrixRotation((*iter).first->getRootEntity());
				(*iter).first->getSkybox()->draw();
			}
			(*iter).second->setCameraMatrix((*iter).first->getRootEntity());
			(*iter).first->getSunlight()->draw();

			
			// @todo this doesnt belong here
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			(*iter).first->getRootEntity()->render();
		}
		t = timerGraphics->stopTimer() / 1000;
		debugout("time for rendering:");
		debugout((long long) t);
	}
	void YGEEngineCoreSingleThreaded::updateSpaceList(YGETimeSpace::YGESpaceList *list){
		int t;
		timerPhysics->startTimer();
		for(YGETimeSpace::YGESpaceList::iterator iter = list->begin(); iter != list->end(); iter++){

			(*iter)->timeStep(delta);
		}
		t = timerPhysics->stopTimer() / 1000;
		debugout("time for physics:");
		debugout((long long) t);

		timerUpdate->startTimer();
		for(YGETimeSpace::YGESpaceList::iterator iter = list->begin(); iter != list->end(); iter++){

			(*iter)->getRootEntity()->update(delta);
		}
		t = timerUpdate->stopTimer() / 1000;
		debugout("time for updateing:");
		debugout((long long) t);

		timerTick->startTimer();
		for(YGETimeSpace::YGESpaceList::iterator iter = list->begin(); iter != list->end(); iter++){

			(*iter)->getRootEntity()->tickChildren(delta);
		}
		
		t = timerTick->stopTimer() / 1000;
		debugout("time for ticking:");
		debugout((long long) t);
	}


	void YGEEngineCoreSingleThreaded::calculateFPSRate(){

		delta = timer->stopTimer();
		accumDelta += delta;
		frames++;
		if(accumDelta > 1000000){
			debugout("FPS:");
			debugout((long long)frames);
			accumDelta = 0;
			std::stringstream s;
			s<<"FPS: "<<frames;

			display->setTitle(s.str().c_str());
			frames = 0;




		}
		//debugout("updating the core took ms");
		//debugout(delta / 1000);


	}

	void YGEEngineCoreSingleThreaded::limitFPS(){
		if(delta < 10000) {
			debugout("less then 10 ms, wait a little");

			SDL_Delay(Uint32((10000-delta) / 1000));
		}
	}


	void YGEEngineCoreSingleThreaded::update(){


	}

	void YGEEngineCoreSingleThreaded::init(){

		delta = 1000;
		accumDelta = 0;


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

		timerGraphics = new YGETimer();
		timerPhysics = new YGETimer();
		timerUpdate = new YGETimer();
		timerTick = new YGETimer();


		logger = YGELogger::getInstance();
		display->init();
		console->init(this);

	}







	void YGEEngineCoreSingleThreaded::shutdown(){
		debugout("prepare to shut down!");
		shutdownNow = true;
	}

}