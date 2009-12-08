#include "YGEEngineCoreSingleThreaded.h"
#include "YGEGraphicsCore.h"
#include <SDL_thread.h> 
#include <SDL_ttf.h>
#include "YGEAudioCore.h"
#include "YGEText.h"



namespace YGECore {
	void YGEEngineCoreSingleThreaded::printTimes(){
		debugout("physics");
		debugout(timerPhysics->getStoppedTime()/1000);
		debugout("graphics rendering");
		debugout(timerGraphics->getStoppedTime()/1000);
		debugout("updating");
		debugout(timerUpdate->getStoppedTime()/1000);
		debugout("ticking");
		debugout(timerTick->getStoppedTime()/1000);
		debugout("altogether");
		debugout(timer->getStoppedTime()/1000);
		debugout("other");
		debugout(timerOther->getStoppedTime()/1000);
	}

	void YGEEngineCoreSingleThreaded::run(){

		debugout("starting the core");

		while(graphics->windowClosed == false && shutdownNow == false){
			if(gamestatechanged) {
				gamestatechanged = false;
				gamestate = newGameState;
				newGameState = NULL;
			}

			if(gamestate->getHasBeenInitialised() == false) {
				gamestate->init();
			}

			//debugout("update the core");


			timer->startTimer();


			graphics->reset();
			graphics->update();



			processEvents();





			if(gamestate != NULL) {
				gamestate->update(delta);

				calcPhysics(delta);
				update();
				updateAbsolutePositions();
				interpolate();
				render();
				tick();

			}

			if(consoleEnabled) {
				console->draw();
			}

			//timerOther->startTimer();

			calculateFPSRate();

			limitFPS();
			//timerOther->stopTimer();
			printTimes();

		}

		debugout("stopping the core");
	}


	
	void YGEEngineCoreSingleThreaded::processSingleEvent(SDL_Event *event){
			switch(event->type){
			case SDL_QUIT:
				graphics->notifyEvent(event);
				break;
			case SDL_KEYDOWN:
				switch(event->key.keysym.sym){
			case SDLK_BACKQUOTE:
				toggleConsole();
				break;
			default:
				if(consoleEnabled){
					console->insertKey(event->key.keysym);
				} else {
					input->notifyEvent(event);
				}
				break;
				}
				break;
			case SDL_KEYUP:
				input->notifyEvent(event);
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:


				break;
			}


	}
	void YGEEngineCoreSingleThreaded::processEvents(){

		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			processSingleEvent(&event);
		}

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

			graphics->setTitle(s.str().c_str());
			frames = 0;
		}
	}

	void YGEEngineCoreSingleThreaded::limitFPS(){
		if(delta < 10000) {
			debugout("less then 10 ms, wait a little");

			SDL_Delay(Uint32((10000-delta) / 1000));
		}
	}


	void YGEEngineCoreSingleThreaded::update(){
		timerUpdate->startTimer();

		for(YGETimeSpace::YGESpaceList::iterator iter = gamestate->getSpacesToUpdate()->begin(); iter != gamestate->getSpacesToUpdate()->end(); iter++){
			(*iter)->getRootEntity()->setTimeOfNewPosition(getTimeSinceGameStarted());
		}


		for(YGETimeSpace::YGESpaceList::iterator iter = gamestate->getSpacesToUpdate()->begin(); iter != gamestate->getSpacesToUpdate()->end(); iter++){

			(*iter)->getRootEntity()->update(delta);
		}
		timerUpdate->stopTimer();

	}

	void YGEEngineCoreSingleThreaded::updateAbsolutePositions(){
		for(YGETimeSpace::YGESceneList::iterator iter = gamestate->getScenesToRender()->begin(); iter != gamestate->getScenesToRender()->end(); iter++){

			(*iter).first->getRootEntity()->updateAbsolutePosition(YGEMath::Vector3(), YGEMath::Quaternion());
		}

	}

	void YGEEngineCoreSingleThreaded::calcPhysics(long long deltaPhysics){
		timerPhysics->startTimer();
		for(YGETimeSpace::YGESpaceList::iterator iter = gamestate->getSpacesToUpdate()->begin(); iter != gamestate->getSpacesToUpdate()->end(); iter++){

			(*iter)->timeStep(deltaPhysics);
		}
		timerPhysics->stopTimer();

	}

	void YGEEngineCoreSingleThreaded::tick(){
		timerTick->startTimer();
		for(YGETimeSpace::YGESpaceList::iterator iter = gamestate->getSpacesToUpdate()->begin(); iter != gamestate->getSpacesToUpdate()->end(); iter++){

			if( (*iter)->getTimeIsRunning() ) {
				(*iter)->getRootEntity()->tickChildren(delta);
			}
		}

		timerTick->stopTimer();

	}
	void YGEEngineCoreSingleThreaded::interpolate(){
		for(YGETimeSpace::YGESceneList::iterator iter = gamestate->getScenesToRender()->begin(); iter != gamestate->getScenesToRender()->end(); iter++){

			// before drawing a new scene, interpolate the positions
			(*iter).first->getRootEntity()->interpolate(getTimeSinceGameStarted());
		}

	}
	void YGEEngineCoreSingleThreaded::render(){
		
		timerGraphics->startTimer();

		for(YGETimeSpace::YGESceneList::iterator iter = gamestate->getScenesToRender()->begin(); iter != gamestate->getScenesToRender()->end(); iter++){


			YGEAudio::YGEAudioCore::getInstance()->renderSpace( (*iter).first, (*iter).second );
			graphics->renderSpace( (*iter).first, (*iter).second  );

		}
		timerGraphics->stopTimer();
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
		graphics = new YGEGraphicsCore();
		input = new YGEInputManager();

		audio = YGEAudio::YGEAudioCore::getInstance();

		timer = new YGETimer();
		timeSinceGameStarted = new YGETimer();
		timeSinceGameStarted->startTimer();

		timerGraphics = new YGETimer();
		timerPhysics = new YGETimer();
		timerUpdate = new YGETimer();
		timerTick = new YGETimer();
		timerOther = new YGETimer();

		logger = YGELogger::getInstance();
		console->init(this);
		graphics->init();

		audio->init();

	}







	void YGEEngineCoreSingleThreaded::shutdown(){
		debugout("prepare to shut down!");
		shutdownNow = true;
	}

	void YGEEngineCoreSingleThreaded::setGameState(YGEGame::YGEGameState* state){
		newGameState = state;
		gamestatechanged = true;
	}

}