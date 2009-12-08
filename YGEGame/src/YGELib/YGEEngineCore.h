#ifndef _YGE_ENGINE_CORE_H_
#define _YGE_ENGINE_CORE_H_

#include "YGEGraphicsCore.h"
#include "YGEInputManager.h"

#include "YGEAudioCore.h"

#include "YGETimer.h"

#include "YGEConsole.h"

#include "YGELogger.h"

#include "YGEGameState.h"

//#include "YGEScene.h"
#include "YGEEntity.h"

#include <SDL_mutex.h>

namespace YGECore {

/**
 * YGE main game engine class
 * @todo just use YGEGraphicsCore... make it nicer... more PFI
 * true object orientation
 */
class YGEEngineCore {
protected:

	/**
	 * pointer to a YGEGraphicsCore. Responsible for graphics rendering stuff.
	 */
	YGEGraphicsCore* graphics;

	/**
	 *
	 *
	 */

	YGEAudio::YGEAudioCore* audio;
	/**
	 * pointer to a YGEInputManager. Responsible for input
	 * as from keyboard, joystick, gamepad or mouse.
	 */
	YGEInputManager* input;

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
	 * This timer is used atm to measure the framerate.
	 */
	YGETimer* timer;

	YGETimer* timerGraphics;
	YGETimer* timerPhysics;
	YGETimer* timerUpdate;
	YGETimer* timerTick;
	YGETimer* timerOther;
	YGETimer* timeSinceGameStarted;

	YGEGame::YGEGameState* gamestate;

	YGEConsole* console;

	bool shutdownNow;

	bool consoleEnabled;

	YGETimeSpace::YGEEntity* scene;

public:

	YGEEngineCore();

	~YGEEngineCore();

	/**
	 * initialises the core
	 * components are allocated and ressources are loaded
	 */
	virtual void init() = 0;

	/**
	 * starts a permanent engine loop, returns if core
	 * decides to shut down (window closed etc...);
	 * init() should be called before starting the render loop
	 */
	virtual void run() = 0;

	/**
	 * free resources etc.
	 */
	virtual void shutdown() = 0;



	virtual void setGameState(YGEGame::YGEGameState* state);

	YGEInputManager* getInputManager();

	long long getTimeSinceGameStarted();

	void toggleConsole();

	void processCommand(const char* command);
};

}
#endif