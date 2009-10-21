#ifndef _YGE_ENGINE_CORE_H_
#define _YGE_ENGINE_CORE_H_

#define USE_SDL

#include "YGESDLDisplay.h"
#include "YGESDLInputManager.h"
#include "YGESDLTimer.h"

#include "YGELogger.h"

#include "YGEGameState.h"

namespace YGECore {

/**
 * YGE main game engine class
 * @todo just use YGEDisplay... make it nicer... more PFI
 * true object orientation
 */
class YGEEngineCore {

	/**
	 * pointer to a YGEDisplay. Responsible for graphics rendering stuff
	 */
	YGESDLDisplay* display;

	/**
	 * pointer to a YGEInputManager. Responsible for input
	 * as from keyboard, joystick, gamepad or mouse
	 */
	YGESDLInputManager* input;

	/**
	 * pointer to a YGELogger
	 * since the YGELogger is a singleton, this is not
	 * really nessesary. The logger can be used for debug output
	 * and the destination of the output can be choosen 
	 * (stdout, YGEConsole, file, etc...)
	 */
	YGELogger* logger;

	/**
	 * pointer to a YGETimer.
	 * This timer is used atm to measure the framerate
	 */
	YGESDLTimer* timer;

public:
	YGEEngineCore();

	~YGEEngineCore();

	/**
	 * initialises the core
	 * components are allocated and ressources are loaded
	 */
	void init();
	
	/**
	 * starts a permanent engine loop, returns if core
	 * decides to shut down (window closed etc...);
	 * init() should be called before starting the render loop
	 */
	void run();

	/**
	 * update the core. should only be called by the core itself
	 */
	void update();

	/**
	 * free resources etc.
	 */
	void shutdown();


	void addGameState(YGEGame::YGEGameState* state){

	}
};

}
#endif