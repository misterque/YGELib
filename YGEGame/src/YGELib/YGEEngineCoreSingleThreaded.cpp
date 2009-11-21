#include "YGEEngineCoreSingleThreaded.h"
#include "YGESDLDisplay.h"
#include <SDL_thread.h> 
#include <SDL_ttf.h>


namespace YGECore {

	void YGEEngineCoreSingleThreaded::run(){

#ifdef _DEBUG
		logger->log("starting the core");
#endif

		while(display->windowClosed == false && shutdownNow == false){
			update();

		}

#ifdef _DEBUG
		logger->log("stopping the core");
#endif
	}



	void YGEEngineCoreSingleThreaded::update(){

#ifdef _DEBUG
		logger->log("update the core");
#endif

		timer->startTimer();

		display->reset();
		display->update();



		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			switch(event.type){
			case SDL_QUIT:
				display->notifyEvent(&event);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:

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
			}

		}



		input->update();
		if(gamestate != 0) {
			gamestate->update();
			//			gamestate->draw(this);
			YGETimeSpace::YGESceneList list = gamestate->getScenesToRender();
			for(YGETimeSpace::YGESceneList::iterator iter = list.begin(); iter != list.end(); iter++){


				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();

				gluPerspective(45.0f,640.0f/480.0f,0.1f,100.0f);


				glMatrixMode( GL_MODELVIEW );
				glLoadIdentity();       
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);

				(*iter).second->setCameraMatrix((*iter).first->getRootEntity());
				(*iter).first->getRootEntity()->render();
				(*iter).first->getRootEntity()->update();
			}
		}

		if(consoleEnabled) {
			console->draw();
		}

		long long delta = timer->stopTimer();

#ifdef _DEBUG
		logger->log("updating the core took ms");
		logger->log(delta / 1000);
#endif

		if(delta < 10000) {
#ifdef _DEBUG
			logger->log("less then 10 ms, wait a little");
#endif

			SDL_Delay(Uint32((10000-delta) / 1000));
		}

	}

	void YGEEngineCoreSingleThreaded::init(){

#ifdef _DEBUG
		logger->log("initialize the core");
		logger->log("using SDL");
#endif


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

		shutdownNow = true;
	}

}