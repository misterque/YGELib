#ifndef _YGE_ENGINE_CORE_SINGLE_THREADED_H_
#define _YGE_ENGINE_CORE_SINGLE_THREADED_H_

#include "YGEEngineCore.h"

namespace YGECore {

	/**
	* YGE main game engine class
	* @todo just use YGEDisplay... make it nicer... more PFI
	* true object orientation
	*/
	class YGEEngineCoreSingleThreaded : public YGEEngineCore {
	private:
		void update();

	public:

		//YGEEngineCoreSingleThreaded();

		//~YGEEngineCoreSingleThreaded();

		/**
		* initialises the core
		* components are allocated and ressources are loaded
		*/
		virtual void init();

		/**
		* starts a permanent engine loop, returns if core
		* decides to shut down (window closed etc...);
		* init() should be called before starting the render loop
		*/
		virtual void run();

		/**
		* free resources etc.
		*/
		virtual void shutdown();

	};

}
#endif