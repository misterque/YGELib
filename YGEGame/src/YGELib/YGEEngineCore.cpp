#include "YGEEngineCore.h"
#include "YGESDLDisplay.h"
#include <SDL_thread.h> 
#include <SDL_mutex.h> 
#include <SDL_ttf.h>

SDL_mutex *render_mutex;


namespace YGECore {

	void YGEEngineCore::run(){

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

	void YGEEngineCore::update(){

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

		TTF_Init();

		console = new YGEConsole();
		YGELogger::getInstance()->setConsole(console);
		display = new YGESDLDisplay();
		input = new YGESDLInputManager();

		timer = new YGESDLTimer();
		timeSinceGameStarted = new YGESDLTimer();
		timeSinceGameStarted->startTimer();

#endif

		logger = YGELogger::getInstance();
		display->init();
		console->init(this);

	}





	void YGEEngineCore::initThreaded(){

#ifdef _DEBUG
		logger->log("initialize the core (threaded)");
#ifdef USE_SDL
		logger->log("using SDL");
		SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTTHREAD);
#endif
#endif

#ifdef USE_SDL


		input = new YGESDLInputManager();

		timer = new YGESDLTimer();
		timeSinceGameStarted = new YGESDLTimer();
		timeSinceGameStarted->startTimer();

#endif

		logger = YGELogger::getInstance();

	}







	void YGEEngineCore::shutdown(){

#ifdef USE_SDL

#endif
		shutdownNow = true;
	}

	YGEEngineCore::YGEEngineCore(){
		gamestate = 0;
		shutdownNow = false;
		render_mutex = SDL_CreateMutex();
		consoleEnabled = false;
	}

	YGEEngineCore::~YGEEngineCore(){
		SDL_Quit();
	}



	int startThreadUpdate(void* thisOne){
		((YGEEngineCore*)thisOne)->threadUpdate( NULL );
		return 0;
	}

	void YGEEngineCore::threadUpdate(void *data){
		while(shutdownNow == false){
			SDL_mutexP(render_mutex);

			YGELogger::getInstance()->log("Thread UPDATE");

			SDL_Event event;

			while(SDL_PollEvent(&event)) {
				switch(event.type){
			case SDL_QUIT:
				display->notifyEvent(&event);

				break;
			case SDL_KEYDOWN:
				//			if
				input->notifyEvent(&event);
				break;
				}

			}

			input->update();
			if(gamestate != 0) {
				gamestate->update();

			}
			SDL_mutexV(render_mutex);

			SDL_Delay(35);
		}
	}

	int startThreadRender(void* thisOne){
		((YGEEngineCore*)thisOne)->threadRender( NULL );
		return 0;
	}
	void YGEEngineCore::threadRender(void *data){
		SDL_mutexP(render_mutex);
		YGELogger::getInstance()->log("init Thread RENDER");

		if(SDL_InitSubSystem(SDL_INIT_VIDEO) == -1) {
			YGELogger::getInstance()->log("initialising subsystem VIDEO failed");
		}

		display = new YGESDLDisplay();
		display->init();
		SDL_mutexV(render_mutex);

		while(display->windowClosed == false && shutdownNow == false){
			SDL_mutexP(render_mutex);

			YGELogger::getInstance()->log("Thread RENDER");
			display->reset();
			display->update();


			SDL_mutexV(render_mutex);

			SDL_Delay(20);
		}
	}

	void YGEEngineCore::threadInput(void *data){
		while(display->windowClosed == false && shutdownNow == false){

		}
	}

	void YGEEngineCore::runThreaded(){
		//startThreadRender(this);

		// create new thread for rendering
		SDL_CreateThread( &startThreadUpdate, this ); 
		// use current thread for updating
		startThreadRender(this);
	}

}