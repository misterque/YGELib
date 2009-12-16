#include "YGEEngineCoreMultiThreaded.h"
#include <SDL_thread.h> 
#include <SDL_mutex.h> 
#include <SDL_ttf.h>


namespace YGECore {

	YGEEngineCoreMultiThreaded::YGEEngineCoreMultiThreaded(){
			statusIsRender = true;

			simulateMutex = SDL_CreateMutex();
			eventMutex = SDL_CreateMutex();

			updateMutex = SDL_CreateMutex();			
			prerenderMutex = SDL_CreateMutex();

			updateCondition = SDL_CreateCond();
			renderCondition = SDL_CreateCond();

			updateThread = NULL;
			simulateThread = NULL;

			gameStateChanged = true;

			newGameState = NULL;
		}

	YGEEngineCoreMultiThreaded::~YGEEngineCoreMultiThreaded(){
		SDL_DestroyMutex( simulateMutex );
		SDL_DestroyMutex( eventMutex );
		SDL_DestroyMutex( updateMutex );
		SDL_DestroyMutex( prerenderMutex );

		SDL_DestroyCond( renderCondition );
		SDL_DestroyCond( updateCondition );
	}

	int startThreadUpdate(void* thisOne){
		((YGEEngineCoreMultiThreaded*)thisOne)->threadUpdate();
		return 0;
	}
	int startThreadSimulate(void* thisOne){
		((YGEEngineCoreMultiThreaded*)thisOne)->threadSimulate();
		return 0;
	}

	void YGEEngineCoreMultiThreaded::threadUpdate(){
		for(;;){
			SDL_mutexP(simulateMutex);
			//SDL_mutexP(sync);
			// wait for signal startupdate


			if(statusIsRender) {
				SDL_mutexP(updateMutex);			
				SDL_CondWait(updateCondition, updateMutex);
			}

			timerUpdate->startTimer();



			update();
			updateAbsolutePositions();


			// signal start render
			debugout("simulation sends signal");

			timerUpdate->stopTimer();
			debugout("update finished:");
			debugout(timerUpdate->getStoppedTime());

			statusIsRender = true;
			SDL_CondSignal(renderCondition);

			SDL_mutexV(simulateMutex);
		}
	}


	void YGEEngineCoreMultiThreaded::threadSimulate(){
		for(;;){
			SDL_mutexP(simulateMutex);

			gamestate->update((long)delta);


			processEvents();


			tick();

			timerPhysics->stopTimer();

			calcPhysics(timerPhysics->getStoppedTime());

			timerPhysics->startTimer();
			SDL_mutexV(simulateMutex);
		}
	}
	void YGEEngineCoreMultiThreaded::run(){

		debugout("starting the core");

		SDL_CreateThread( &startThreadUpdate, this ); 

		SDL_CreateThread( &startThreadSimulate, this ); 

		while(graphics->windowClosed == false && shutdownNow == false){

			if(gameStateChanged) {
				gameStateChanged = false;
				gamestate = newGameState;
				newGameState = NULL;

				if(updateThread != NULL) {
					SDL_KillThread(updateThread);
					SDL_KillThread(simulateThread);

				}
			}

			debugout("render etc");

			if(gamestate->getHasBeenInitialised() == false) {
				gamestate->init();
			}

			timer->startTimer();


			// signal startupdate and start with cleaning the buffers etc
			//SDL_mutexV(updateMutex);
			//SDL_mutexP(sync);

			statusIsRender = false;
			SDL_CondSignal(updateCondition);
			//SDL_mutexV(sync);

			debugout("render sended signal");


			graphics->reset();
			graphics->update();

			// wait for signal startrender
			debugout("render waiting for signal");

			if(!statusIsRender){
				SDL_mutexP(prerenderMutex);
				SDL_CondWait(renderCondition, prerenderMutex);
			}

			debugout("render signaled");

			SDL_mutexP(eventMutex);
			SDL_Event event;

			while(SDL_PollEvent(&event)) {
				eventList.push_back(event);
			}
			SDL_mutexV(eventMutex);



			interpolate();


			render();



			if(consoleEnabled) {
				console->draw();
			}

			//timerOther->startTimer();

			calculateFPSRate();

			limitFPS();
			//timerOther->stopTimer();
			//printTimes();

		}

		debugout("stopping the core");
	}


	void YGEEngineCoreMultiThreaded::processEvents(){

		SDL_mutexP(eventMutex);
		for(std::list<SDL_Event>::iterator iter = eventList.begin(); iter != eventList.end(); iter++){
			processSingleEvent(&(*iter));
		}
		eventList.clear();
		SDL_mutexV(eventMutex);

	}


}