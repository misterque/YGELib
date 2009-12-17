#include "YGEEngineCoreSingleThreaded.h"
#include "YGEGraphicsCore.h"
#include <SDL_thread.h> 
#include <SDL_ttf.h>
#include "YGEAudioCore.h"
#include "YGEText.h"


long long timerAccumTick;
long long timerAccumPhysics;
long long timerAccumGraphics;
long long timerAccumUpdate;
long long timerAccumOther;



namespace YGECore {
	void YGEEngineCoreSingleThreaded::printTimes(){
		debugout("physics");
		debugout(timerAccumPhysics/1000.0f/double(frames));
		debugout("graphics");
		debugout(timerAccumGraphics/1000.0f/double(frames));
		debugout("updating");
		debugout(timerAccumUpdate/1000.0f/double(frames));
		debugout("ticking");
		debugout(timerAccumTick/1000.0f/double(frames));
		debugout("other");
		debugout(timerAccumOther/1000.0f/double(frames));
	}

	void YGEEngineCoreSingleThreaded::run(){

		debugout("starting the core");

		while(graphics->windowClosed == false && shutdownNow == false){
			debugout("starting core cycle");

			// if needed, change the gamestate
			if(gameStateChanged) {

				debugout("changing gamestate");

				gameStateChanged = false;
				gamestate = newGameState;
				newGameState = NULL;
			}

			// if needed, first initialize the gamesteate
			if(gamestate->getHasBeenInitialised() == false) {
				debugout("initializing gamestate");

				gamestate->init();


			}


			// start timer for fps calculation
			timer->startTimer();





			// process all input events
			processEvents();

			// do all the engine stuff
			if(gamestate != NULL) {

				gamestate->update((long)delta);

				calcPhysics(delta);
				update();
				updateAbsolutePositions();
				interpolate();

				// do some prerendering
				timerOther->startTimer();
				graphics->reset();
				graphics->update();
				timerOther->stopTimer();
				render();
				tick();

			}

			// draw the console
			if(consoleEnabled) {
				console->draw();
			}

			//timerOther->startTimer();


			// stop the timer for fps calulation
			delta = timer->stopTimer();

			timerAccumTick += timerTick->getStoppedTime();
			timerAccumPhysics += timerPhysics->getStoppedTime();
			timerAccumGraphics += timerGraphics->getStoppedTime();
			timerAccumUpdate += timerUpdate->getStoppedTime();
			timerAccumOther += timerOther->getStoppedTime();


			limitFPS();
			calculateFPSRate();

			// give some debuggin and profiling information


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
					// send input to the console
					console->insertKey(event->key.keysym);
				} else {
					// send keyboard down input etc to the input manager
					input->notifyEvent(event);
				}
				break;
				}
				break;
			case SDL_KEYUP:
				//send keyboard up to the input manager
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


		accumDelta += delta;




		frames++;
		if(accumDelta > 1000000){
			debugout("FPS:");
			debugout((long long)frames);
			accumDelta = 0;


			std::stringstream s;
			s<<"FPS: "<<frames;

			framesPerSecond = frames;

			graphics->setTitle(s.str().c_str());


#ifdef _DEBUG
			printTimes();

			timerAccumTick = 0;
			timerAccumPhysics = 0;
			timerAccumGraphics = 0;
			timerAccumUpdate = 0;
			timerAccumOther = 0;
			frames = 0;
#endif
		}
	}

	void YGEEngineCoreSingleThreaded::limitFPS(){
		if(delta < 10000) {
			debugout("less then 10 ms, wait a little");

			SDL_Delay(Uint32((10000-delta) / 1000));
			delta = 10000;
		}
	}


	void YGEEngineCoreSingleThreaded::update(){
		timerUpdate->startTimer();

		for(YGETimeSpace::YGESpaceList::iterator iter = gamestate->getSpacesToUpdate()->begin(); iter != gamestate->getSpacesToUpdate()->end(); iter++){
			(*iter)->getRootEntity()->setTimeOfNewPosition(getTimeSinceGameStarted());
		}


		for(YGETimeSpace::YGESpaceList::iterator iter = gamestate->getSpacesToUpdate()->begin(); iter != gamestate->getSpacesToUpdate()->end(); iter++){

			(*iter)->getRootEntity()->update((long)delta);
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
				(*iter)->getRootEntity()->tickChildren((long)delta);
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

		timerAccumTick = 0;
		timerAccumPhysics = 0;
		timerAccumGraphics = 0;
		timerAccumUpdate = 0;
		timerAccumOther = 0;

		gamestate = 0;
		shutdownNow = false;
		consoleEnabled = false;

		debugout("initialize the core");

		// init all subsystems

		YGELogger::getInstance()->log("Initializing SDL Video");
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			throw YGEExceptionSubsystemError("SDL Video init");
			return;
		}

		if (TTF_Init() != 0) {
			throw YGEExceptionSubsystemError("TTF init");
			return;
		}


		console = new YGEConsole();
		YGELogger::getInstance()->setConsole(console);
		graphics = new YGEGraphics::YGEGraphicsCore();
		input = new YGEInput::YGEInputManager();

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
		gameStateChanged = true;
	}

}