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
	* YGE main game engine class in multithreading mode
	*
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

		/**
		 * list of events for querying and processing events seperatly
		 */
		std::list<SDL_Event> eventList;

		SDL_Thread* updateThread;
		SDL_Thread* simulateThread;

	public:

		YGEEngineCoreMultiThreaded();

		~YGEEngineCoreMultiThreaded();

		/**
		* starts a permanent engine loop with a seperate thread for physics
		* init() should be called before 
		*/
		virtual void run();

		/**
		 * starting point for update thread
		 */
		void threadUpdate();

		/**
		 * starting point fot the simulation thread
		 */
		void threadSimulate();

		/**
		 * in multithreading mode, querying and processing of events is
		 * decoupled, so this function processes all events from the events list
		 */
		void processEvents();






	};

}
#endif