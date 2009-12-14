/**
 * @file
 * @author Dirk Fortmeier
 * @date ?
 */

#ifndef _YGE_ENGINE_CORE_MULTI_THREADED_H_
#define _YGE_ENGINE_CORE_MULTI_THREADED_H_

#include "YGEEngineCoreSingleThreaded.h"

#include "SDL.h"
#include "SDL_thread.h"

#include <list>

namespace YGECore {

	/**
	* YGE main game engine class
	* @todo just use YGEGraphicsCore... make it nicer... more PFI
	* true object orientation
	*/
	class YGEEngineCoreMultiThreaded : public YGEEngineCoreSingleThreaded {
	protected:
		SDL_mutex* simulateMutex;


		SDL_mutex* updateMutex;
		SDL_mutex* prerenderMutex;
		SDL_cond* updateCondition;
		SDL_cond* renderCondition;

		bool statusIsRender;
	
		SDL_mutex* eventMutex;

		std::list<SDL_Event> events;

		SDL_Thread* updateThread;
		SDL_Thread* simulateThread;

	public:

		YGEEngineCoreMultiThreaded(){
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

		//@todo destroy the mutexes and conditions
//		~YGEEngineCoreMultiThreaded();

		/**
		* starts a permanent engine loop with a seperate thread for physics
		* init() should be called before 
		*/
		virtual void run();

		void threadUpdate();

		void threadSimulate();

		void processEvents();






	};

}
#endif