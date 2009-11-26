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

		/**
		 * time elapsed between two frames
		 */
		long long delta;

		/**
		 * stores time since last output of FPS rate
		 * if > 1 sec debugout frames
		 */
		long long accumDelta;

		/**
		 * frame counter for FPS rate
		 */
		int frames;

		void update();

		void processEvents();

		void renderSceneList(YGETimeSpace::YGESceneList *list);

		void updateSpaceList(YGETimeSpace::YGESpaceList *list);

		void calculateFPSRate();

		void limitFPS();

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