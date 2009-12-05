#ifndef _YGE_ENGINE_CORE_MULTI_THREADED_H_
#define _YGE_ENGINE_CORE_MULTI_THREADED_H_

#include "YGEEngineCore.h"

namespace YGECore {

	/**
	* YGE main game engine class
	* @todo just use YGEGraphicsCore... make it nicer... more PFI
	* true object orientation
	*/
	class YGEEngineCoreMultiThreaded : public YGEEngineCore {
	protected:

	public:

		YGEEngineCoreMultiThreaded();

		~YGEEngineCoreMultiThreaded();
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